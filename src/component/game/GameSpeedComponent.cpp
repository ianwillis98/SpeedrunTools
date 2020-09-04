#include "GameSpeedComponent.h"
#include "../../utils/ImGuiExtensions.h"

GameSpeedComponent::GameSpeedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void GameSpeedComponent::onLoad()
{

}

void GameSpeedComponent::onUnload()
{

}

void GameSpeedComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Customize game speed");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    float gameSpeed = this->getGameSpeed();
    if (ImGui::SliderFloat("Game Speed", &gameSpeed, 0.05f, 5.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameSpeed](GameWrapper *gw) {
            this->setGameSpeed(gameSpeed);
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

    ImGui::PopID();
}

float GameSpeedComponent::getGameSpeed()
{
    return this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getFloatValue();
}

void GameSpeedComponent::setGameSpeed(float speed)
{
    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").setValue(speed);
}
