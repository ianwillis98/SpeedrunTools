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

    ImGui::Text("Custom Game Gravity");

//    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
//
//    ImGui::SameLine();
//    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
//    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    float gameGravity = this->getGameGravity();
    if (ImGui::SliderFloat("Game Gravity", &gameGravity, -2000.0f, 2000.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this, gameGravity](GameWrapper *gw) {
            this->setGameGravity(gameGravity);
        });
    }

    if (ImGui::Button("Default"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(-650.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(-0.001f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Inverse"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(650.0f);
        });
    }

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
