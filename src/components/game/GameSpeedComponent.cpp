#include "GameSpeedComponent.h"
#include "../../utils/ImGuiExtensions.h"

GameSpeedComponent::GameSpeedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void GameSpeedComponent::onLoad()
{
    CVarWrapper componentEnabled = this->plugin->cvarManager->registerCvar("st_game_speed_enabled", "1", "Is custom game speed enabled");
    componentEnabled.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onComponentEnabledChanged();
    });

    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    svSoccarGameSpeedCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onSvSoccarGameSpeedChanged(oldValue, cvar);
    });

    std::string currentGameSpeed = svSoccarGameSpeedCVar.getStringValue();
    CVarWrapper gameSpeedCVar = this->plugin->cvarManager->registerCvar("st_game_speed", currentGameSpeed, "Current game speed");
    gameSpeedCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onGameSpeedChanged(oldValue, cvar);
    });
}

void GameSpeedComponent::onUnload()
{

}

void GameSpeedComponent::render()
{
    bool enabled = this->isComponentEnabled();
    if (ImGui::Checkbox("Customize Game Speed", &enabled))
    {
        this->setComponentEnabled(enabled);
    }

    bool isEnabled = this->isComponentEnabled();
    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(!isEnabled || !isInFreeplay);

    float speed = this->getGameSpeed();
    if (ImGui::SliderFloat("Game Speed", &speed, 0.05f, 5.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, speed](GameWrapper *gw) {
            this->setGameSpeed(speed);
        });
    }

    if (ImGui::Button("Default (1.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeed(1.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Slo-mo (0.67)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeed(0.67f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Fast-mo (1.17)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeed(1.17f);
        });
    }

    ImGuiExtensions::PopDisabledStyleIf(!isEnabled || !isInFreeplay);
}

bool GameSpeedComponent::isComponentEnabled()
{
    return this->plugin->cvarManager->getCvar("st_game_speed_enabled").getBoolValue();
}

void GameSpeedComponent::setComponentEnabled(bool enabled)
{
    this->plugin->cvarManager->getCvar("st_game_speed_enabled").setValue(enabled);
}

void GameSpeedComponent::onComponentEnabledChanged()
{
    if (this->isComponentEnabled())
    {
        this->plugin->cvarManager->getCvar("st_game_speed").notify();
    }
    else
    {
        this->setSvSoccarGameSpeed(1.0f);
    }
}

float GameSpeedComponent::getSvSoccarGameSpeed()
{
    return this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getFloatValue();
}

void GameSpeedComponent::setSvSoccarGameSpeed(float speed)
{
    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").setValue(speed);
}

void GameSpeedComponent::onSvSoccarGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (!this->isComponentEnabled()) return;

    if (this->getGameSpeed() != this->getSvSoccarGameSpeed())
    {
        this->setGameSpeed(this->getSvSoccarGameSpeed());
    }
}

float GameSpeedComponent::getGameSpeed()
{
    return this->plugin->cvarManager->getCvar("st_game_speed").getFloatValue();
}

void GameSpeedComponent::setGameSpeed(float speed)
{
    this->plugin->cvarManager->getCvar("st_game_speed").setValue(speed);
}

void GameSpeedComponent::onGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (!this->isComponentEnabled()) return;

    if (this->getSvSoccarGameSpeed() != this->getGameSpeed())
    {
        this->setSvSoccarGameSpeed(this->getGameSpeed());
    }
}
