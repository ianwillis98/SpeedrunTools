#include "GameGravityComponent.h"
#include "../../utils/ImGuiExtensions.h"

GameGravityComponent::GameGravityComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void GameGravityComponent::onLoad()
{
    CVarWrapper componentEnabled = this->plugin->cvarManager->registerCvar("st_game_gravity_enabled", "1", "Is custom gravity enabled");
    componentEnabled.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onComponentEnabledChanged();
    });

    CVarWrapper svSoccarGameGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    svSoccarGameGravityCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onSvSoccarGameGravityChanged();
    });

    std::string currentGravity = svSoccarGameGravityCVar.getStringValue();
    CVarWrapper gameGravityCVar = this->plugin->cvarManager->registerCvar("st_game_gravity", currentGravity, "Current game gravity");
    gameGravityCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onGameGravityChanged();
    });
}

void GameGravityComponent::onUnload()
{

}

void GameGravityComponent::render()
{
    bool enabled = this->isComponentEnabled();
    if (ImGui::Checkbox("Customize Game Gravity", &enabled))
    {
        this->setComponentEnabled(enabled);
    }

    bool isEnabled = this->isComponentEnabled();
    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(!isEnabled || !isInFreeplay);

    float gravity = this->getGameGravity();
    if (ImGui::SliderFloat("Game Gravity", &gravity, -5000.0f, 5000.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gravity](GameWrapper *gw) {
            this->setGameGravity(gravity);
        });
    }

    if (ImGui::Button("Default (-650.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(-650.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero (-0.001)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(-0.001f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Inverted (650.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(650.0f);
        });
    }

    ImGuiExtensions::PopDisabledStyleIf(!isEnabled || !isInFreeplay);
}

bool GameGravityComponent::isComponentEnabled()
{
    return this->plugin->cvarManager->getCvar("st_game_gravity_enabled").getBoolValue();
}

void GameGravityComponent::setComponentEnabled(bool enabled)
{
    this->plugin->cvarManager->getCvar("st_game_gravity_enabled").setValue(enabled);
}

void GameGravityComponent::onComponentEnabledChanged()
{
    if (this->isComponentEnabled())
    {
        this->plugin->cvarManager->getCvar("st_game_gravity").notify();
    }
    else
    {
        this->setSvSoccarGameGravity(-650.0f);
    }
}

float GameGravityComponent::getSvSoccarGameGravity()
{
    return this->plugin->cvarManager->getCvar("sv_soccar_gravity").getFloatValue();
}

void GameGravityComponent::setSvSoccarGameGravity(float gravity)
{
    this->plugin->cvarManager->getCvar("sv_soccar_gravity").setValue(gravity);
}

void GameGravityComponent::onSvSoccarGameGravityChanged()
{
    if (!this->isComponentEnabled()) return;

    if (this->getGameGravity() != this->getSvSoccarGameGravity())
    {
        this->setGameGravity(this->getSvSoccarGameGravity());
    }
}

float GameGravityComponent::getGameGravity()
{
    return this->plugin->cvarManager->getCvar("st_game_gravity").getFloatValue();
}

void GameGravityComponent::setGameGravity(float gravity)
{
    this->plugin->cvarManager->getCvar("st_game_gravity").setValue(gravity);
}

void GameGravityComponent::onGameGravityChanged()
{
    if (!this->isComponentEnabled()) return;

    if (this->getSvSoccarGameGravity() != this->getGameGravity())
    {
        this->setSvSoccarGameGravity(this->getGameGravity());
    }
}
