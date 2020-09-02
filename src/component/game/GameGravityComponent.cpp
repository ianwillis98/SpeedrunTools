#include "GameGravityComponent.h"
#include "../../utils/ImGuiExtensions.h"

GameGravityComponent::GameGravityComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void GameGravityComponent::onLoad()
{

}

void GameGravityComponent::onUnload()
{

}

void GameGravityComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Customize game gravity");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);

    float gameGravity = this->getGameGravity();
    if (ImGui::SliderFloat("Game Gravity", &gameGravity, -5000.0f, 5000.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameGravity](GameWrapper *gw) {
            this->setGameGravity(gameGravity);
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

    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);

    ImGui::PopID();
}

float GameGravityComponent::getGameGravity()
{
    return this->plugin->cvarManager->getCvar("sv_soccar_gravity").getFloatValue();
}

void GameGravityComponent::setGameGravity(float gravity)
{
    this->plugin->cvarManager->getCvar("sv_soccar_gravity").setValue(gravity);
}
