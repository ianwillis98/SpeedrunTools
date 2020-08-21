#include "SaveStateToolkit.h"
#include "../../services/MultiEventHooker.h"
#include <utils/customrotator.h>

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
    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindlength", "6.0", "Rewind length");
    rewindLengthCVar.bindTo(this->rewindLength);
    rewindLengthCVar.addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
        this->onRewindLengthCvarChanged(oldValue, cvar);
    });

    CVarWrapper rewindSaveIntervalCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindsaveinterval", "0.1", "Rewind save interval");
    rewindSaveIntervalCVar.bindTo(this->rewindSaveInterval);
    rewindSaveIntervalCVar.addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
        this->onRewindSaveIntervalChanged(oldValue, cvar);
    });

    MultiEventHooker::getInstance().hookEvent(plugin, "Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &evenName) {
        this->onPhysicsTick();
    });

    this->plugin->cvarManager->registerNotifier("st_ss_save", [this](const std::vector<std::string> &commands) {
        this->saveCurrentState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_load", [this](const std::vector<std::string> &commands) {
        this->loadSaveState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_rewind", [this](const std::vector<std::string> &commands) {
        this->rewindState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateToolkit::onUnload()
{

}

void SaveStateToolkit::render()
{
    ImGui::Spacing();

    this->renderSaveStateView();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->renderRewindView();

    ImGui::Spacing();
}

void SaveStateToolkit::onPhysicsTick()
{
    CustomRotator r;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    SaveState ss(server);
    this->rewindBuffer.push(ss);
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

void SaveStateToolkit::rewindState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (this->rewindBuffer.empty()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    SaveState ss = this->rewindBuffer.getFrontAndRemoveOthers();

    ss.applyTo(server);
}

void SaveStateToolkit::setRewindLengthCVar(float length)
{
    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->getCvar("st_ss_rewindlength");
    if (rewindLengthCVar.IsNull()) return;

    rewindLengthCVar.setValue(length);
}

void SaveStateToolkit::onRewindLengthCvarChanged(const std::string &oldValue, CVarWrapper cvar)
{
    this->rewindBuffer = SaveStateBuffer(cvar.getIntValue() * 120);
}

void SaveStateToolkit::setRewindSaveIntervalCVar(float interval)
{
    CVarWrapper rewindSaveIntervalCVar = this->plugin->cvarManager->getCvar("st_ss_rewindsaveinterval");
    if (rewindSaveIntervalCVar.IsNull()) return;

    rewindSaveIntervalCVar.setValue(interval);
}

void SaveStateToolkit::onRewindSaveIntervalChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    this->rewindBuffer.clear();
}

void SaveStateToolkit::renderSaveStateView()
{
    ImGui::Text("save state");
}

void SaveStateToolkit::renderRewindView()
{
    ImGui::Text("rewind");
}
