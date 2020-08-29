#include "SaveStateComponent.h"
#include "../../utils/ImGuiExtensions.h"

SaveStateComponent::SaveStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), saveState(), isSaved(false)
{

}

void SaveStateComponent::onLoad()
{
    this->plugin->cvarManager->registerNotifier("st_ss_save", [this](const std::vector<std::string> &commands) {
        this->save();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_load", [this](const std::vector<std::string> &commands) {
        this->load();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateComponent::onUnload()
{

}

void SaveStateComponent::render()
{
    ImGui::Text("Save the current game state to be loaded whenever");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);

    if (ImGui::Button("Save state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->save();
        });
    }
    ImGui::SameLine();
    ImGuiExtensions::PushDisabledStyleIf(isInFreeplay && !this->isSaved);
    if (ImGui::Button("Load state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->load();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(isInFreeplay && !this->isSaved);

    if (this->isSaved)
    {
        this->saveState.render("save state");
    }

    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
}

void SaveStateComponent::save()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState = SaveState(server);
    this->isSaved = true;
}

void SaveStateComponent::load()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (!this->isSaved) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState.applyTo(server);
}

bool SaveStateComponent::isStateSaved() const
{
    return this->isSaved;
}
