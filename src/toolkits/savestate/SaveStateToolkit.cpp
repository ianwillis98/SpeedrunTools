#include "SaveStateToolkit.h"
#include "../../services/MultiEventHooker.h"
#include <utils/customrotator.h>

const bool SaveStateToolkit::DEFAULT_IS_REWIND_ACTIVE = true;
const float SaveStateToolkit::DEFAULT_REWIND_LENGTH = 6.0f;
const float SaveStateToolkit::DEFAULT_REWIND_SAVE_INTERVAL = 1.0f;

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), isRewindActive(std::make_shared<bool>()), rewindLength(std::make_shared<float>()),
          rewindSaveInterval(std::make_shared<float>()), isStateSaved(false), rewindBuffer(rewindLength)
{

}

std::string SaveStateToolkit::title()
{
    return "Save States";
}

void SaveStateToolkit::onLoad()
{
    CVarWrapper isRewindActiveCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindactive", std::to_string(DEFAULT_IS_REWIND_ACTIVE),
                                                                             "Is rewind active");
    isRewindActiveCVar.bindTo(this->isRewindActive);
    isRewindActiveCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onIsRewindActiveCVarChanged(oldValue, cvar);
    });

    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindlength", std::to_string(DEFAULT_REWIND_LENGTH),
                                                                           "Rewind length");
    rewindLengthCVar.bindTo(this->rewindLength);
    rewindLengthCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onRewindLengthCvarChanged(oldValue, cvar);
    });

    CVarWrapper rewindSaveIntervalCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindsaveinterval",
                                                                                 std::to_string(DEFAULT_REWIND_SAVE_INTERVAL),
                                                                                 "Rewind save interval");
    rewindSaveIntervalCVar.bindTo(this->rewindSaveInterval);
    rewindSaveIntervalCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onRewindSaveIntervalChanged(oldValue, cvar);
    });

    MultiEventHooker::getInstance().hookEvent(plugin, "Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &evenName) {
        this->onPhysicsTick();
    });

    this->plugin->cvarManager->registerNotifier("st_ss_save", [this](const std::vector<std::string> &commands) {
        this->onSaveState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_load", [this](const std::vector<std::string> &commands) {
        this->onLoadState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_rewind", [this](const std::vector<std::string> &commands) {
        this->onRewindState();
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
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    if (*this->isRewindActive)
    {
        ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (server.IsNull()) return;

        float currentTime = server.GetSecondsElapsed();

        this->rewindBuffer.empty();
        if (this->rewindBuffer.empty() || currentTime > previousSaveTime + *this->rewindSaveInterval)
        {
            SaveState ss(server);
            this->rewindBuffer.push(ss);
            this->previousSaveTime = currentTime;
            this->plugin->cvarManager->log("saving state");
        }
    }
}

void SaveStateToolkit::onSaveState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState = SaveState(server);
    this->isStateSaved = true;
}

void SaveStateToolkit::onLoadState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (!this->isStateSaved) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState.applyTo(server);
}

void SaveStateToolkit::onRewindState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (this->rewindBuffer.empty()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->rewindBuffer.removeAllButFront();
    SaveState ss = this->rewindBuffer.front();
    ss.applyTo(server);
}

void SaveStateToolkit::setIsRewindActiveCVar(bool active)
{
    CVarWrapper isRewindActiveCVar = this->plugin->cvarManager->getCvar("st_ss_rewindactive");
    if (isRewindActiveCVar.IsNull()) return;

    isRewindActiveCVar.setValue(active);
}

void SaveStateToolkit::onIsRewindActiveCVarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (!*this->isRewindActive)
    {
        this->rewindBuffer.clear();
    }
}

void SaveStateToolkit::setRewindLengthCVar(float length)
{
    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->getCvar("st_ss_rewindlength");
    if (rewindLengthCVar.IsNull()) return;

    rewindLengthCVar.setValue(length);
}

void SaveStateToolkit::onRewindLengthCvarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    //this->rewindBuffer = SaveStateBuffer((int) (*this->rewindLength * (1.0f / *this->rewindSaveInterval)));
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
