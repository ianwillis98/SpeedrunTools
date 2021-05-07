#include "SaveStateComponent.h"

const std::string SaveStateComponent::SaveStateCVarName = "speedrun_savestate_save";
const std::string SaveStateComponent::LoadStateCVarName = "speedrun_savestate_load";

SaveStateComponent::SaveStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          isGameStateSaved(false),
          gameSaveState()
{
    this->plugin->cvarManager->registerNotifier(SaveStateCVarName, [this](const std::vector<std::string> &commands) {
        this->saveCurrentGameState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier(LoadStateCVarName, [this](const std::vector<std::string> &commands) {
        this->loadPreviousGameState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateComponent::render()
{
    ImGui::PushID(this);
    ImGuiExtensions::BigSpacing();

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
    ImGui::Spacing();

    this->gameSaveState.render();
    ImGuiExtensions::PopDisabledStyleIf(isInFreeplay && !this->isGameStateSaved);
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
    ImGui::PopID();
}

void SaveStateComponent::onEvent(const std::string &eventName, bool post, void *params)
{

}

void SaveStateComponent::saveCurrentGameState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->gameSaveState = GameState(server);
    this->isGameStateSaved = true;
}

void SaveStateComponent::loadPreviousGameState()
{
    if (!this->isGameStateSaved) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->gameSaveState.applyTo(server);
}
