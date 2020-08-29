#include "SaveStateComponent.h"
#include "../../utils/ImGuiExtensions.h"

SaveStateComponent::SaveStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), saveState(), isSaved(false)
{

}

void SaveStateComponent::onLoad()
{
    CVarWrapper componentEnabled = this->plugin->cvarManager->registerCvar("st_savestate_save_enabled", "1", "Are save states enabled");
    componentEnabled.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onComponentEnabledChanged();
    });

    this->plugin->cvarManager->registerNotifier("st_savestate_save", [this](const std::vector<std::string> &commands) {
        this->save();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_savestate_load", [this](const std::vector<std::string> &commands) {
        this->load();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateComponent::onUnload()
{

}

void SaveStateComponent::render()
{
    bool isComponentEnabled = this->isComponentEnabled();
    if (ImGui::Checkbox("Save the current game state to be loaded whenever", &isComponentEnabled))
    {
        this->plugin->gameWrapper->Execute([this, isComponentEnabled](GameWrapper *gw) {
            this->setComponentEnabled(isComponentEnabled);
        });
    }

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGuiExtensions::PushDisabledStyleIf(!isComponentEnabled || !isInFreeplay);

    if (ImGui::Button("Save state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->save();
        });
    }
    ImGui::SameLine();
    ImGuiExtensions::PushDisabledStyleIf(isComponentEnabled && isInFreeplay && !this->isSaved);
    if (ImGui::Button("Load state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->load();
        });
    }

    this->saveState.render("save state");

    ImGuiExtensions::PopDisabledStyleIf(isComponentEnabled && isInFreeplay && !this->isSaved);

    ImGuiExtensions::PopDisabledStyleIf(!isComponentEnabled || !isInFreeplay);
}

void SaveStateComponent::save()
{
    if (!this->isComponentEnabled()) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState = GameState(server);
    this->isSaved = true;
}

void SaveStateComponent::load()
{
    if (!this->isComponentEnabled()) return;
    if (!this->isSaved) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState.applyTo(server);
}

bool SaveStateComponent::isComponentEnabled()
{
    return this->plugin->cvarManager->getCvar("st_savestate_save_enabled").getBoolValue();
}

void SaveStateComponent::setComponentEnabled(bool enabled)
{
    this->plugin->cvarManager->getCvar("st_savestate_save_enabled").setValue(enabled);
}

void SaveStateComponent::onComponentEnabledChanged()
{
    if (!this->isComponentEnabled())
    {
        this->isSaved = false;
        this->saveState = GameState();
    }
}

bool SaveStateComponent::isStateSaved() const
{
    return this->isSaved;
}


