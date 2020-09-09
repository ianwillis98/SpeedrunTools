#include "SaveStateComponent.h"
#include "../../utils/ImGuiExtensions.h"

SaveStateComponent::SaveStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), saveState(), isSaved(false)
{

}

void SaveStateComponent::onLoad()
{

}

void SaveStateComponent::onUnload()
{

}

void SaveStateComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Save and Load Game States");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
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

    this->saveState.render();
    ImGuiExtensions::PopDisabledStyleIf(isInFreeplay && !this->isSaved);

    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);

    ImGui::PopID();
}

void SaveStateComponent::save()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState = GameState(server);
    this->isSaved = true;
}

void SaveStateComponent::load()
{
    if (!this->isSaved) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState.applyTo(server);
}

bool SaveStateComponent::isStateSaved()
{
    return this->isSaved;
}
