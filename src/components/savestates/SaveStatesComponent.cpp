#include "SaveStatesComponent.h"

const std::string SaveStatesComponent::SaveStateCVarName = "speedrun_savestate_save";
const std::string SaveStatesComponent::LoadStateCVarName = "speedrun_savestate_load";

SaveStatesComponent::SaveStatesComponent(NetcodePlugin *plugin)
        : PluginComponentBase(plugin),
          isGameStateSaved(false),
          savedGameState()
{
    this->plugin->cvarManager->registerNotifier(SaveStateCVarName, [this](const std::vector<std::string> &commands) {
        this->saveCurrentGameState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(LoadStateCVarName, [this](const std::vector<std::string> &commands) {
        this->loadPreviousGameState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStatesComponent::render()
{
    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    if (ImGui::Button("Save State"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->saveCurrentGameState();
        });
    }
    ImGui::SameLine();
    ImGuiExtensions::PushDisabledStyleIf(isInFreeplay && !this->isGameStateSaved);
    if (ImGui::Button("Load State"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->loadPreviousGameState();
        });
    }
    ImGuiExtensions::BigSeparator();

    this->savedGameState.render();
    ImGuiExtensions::PopDisabledStyleIf(isInFreeplay && !this->isGameStateSaved);
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
}

void SaveStatesComponent::saveCurrentGameState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->savedGameState = GameState(server);
    this->isGameStateSaved = true;
}

void SaveStatesComponent::loadPreviousGameState()
{
    if (!this->isGameStateSaved) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->savedGameState.applyTo(server);
}
