#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "SaveStateToolkit.h"
#include "../../services/MultiEventHooker.h"

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), isStateSaved(false), rewindBuffer(6 * 120)
{
    this->rewindLength = std::make_shared<float>();
    this->rewindSaveInterval = std::make_shared<float>();
}

std::string SaveStateToolkit::title()
{
    return "Save States";
}

void SaveStateToolkit::onLoad()
{
    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->registerCvar("fpt_ss_rewindlength", "6.0", "Rewind length");
    rewindLengthCVar.bindTo(this->rewindLength);
    rewindLengthCVar.addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
        this->rewindBuffer = SaveStateBuffer(cvar.getIntValue() * 120);
    });

    CVarWrapper rewindSaveIntervalCVar = this->plugin->cvarManager->registerCvar("fpt_ss_rewindsaveinterval", "0.1", "Rewind save interval");
    rewindSaveIntervalCVar.bindTo(this->rewindSaveInterval);
    rewindSaveIntervalCVar.addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
        this->rewindBuffer.clear();
    });

    MultiEventHooker::getInstance().hookEvent(plugin, "Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &evenName) {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (server.IsNull()) return;

        SaveState ss(server);

        this->rewindBuffer.push(ss);
    });

    this->plugin->cvarManager->registerNotifier("fpt_ss_save", [this](const std::vector<std::string> &commands) {
        this->saveCurrentState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_load", [this](const std::vector<std::string> &commands) {
        this->loadSaveState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_rewind", [this](const std::vector<std::string> &commands) {
        this->rewindState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateToolkit::onUnload()
{

}

void SaveStateToolkit::render()
{
    ImGui::Text("hello");
}

void SaveStateToolkit::saveCurrentState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState = SaveState(server);
    this->isStateSaved = true;
}

void SaveStateToolkit::loadSaveState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (!this->isStateSaved) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState.applyTo(server);
}

void SaveStateToolkit::setRewindLength(float length)
{
    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->getCvar("fpt_ss_rewindlength");
    if (rewindLengthCVar.IsNull()) return;

    length = (std::max)(length, 0.0f);

    rewindLengthCVar.setValue(length);
}

void SaveStateToolkit::rewindState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (this->rewindBuffer.empty()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    SaveState ss = this->rewindBuffer.getFrontAndRemoveOthers();

    ss.applyTo(server);
}
