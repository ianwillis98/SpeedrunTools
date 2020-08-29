#include "GameGravityComponent.h"
#include "../../utils/ImGuiExtensions.h"

GameGravityComponent::GameGravityComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), svSoccarGameGravity(nullptr), gameGravity(nullptr)
{

}

void GameGravityComponent::onLoad()
{
    CVarWrapper svSoccarGameGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    if (svSoccarGameGravityCVar.IsNull())
    {
        this->plugin->cvarManager->log("sv_soccar_gravity was null. Custom gravity won't work.");
    }
    this->svSoccarGameGravity = std::make_unique<CVarWrapper>(svSoccarGameGravityCVar);
    svSoccarGameGravityCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onSvSoccarGameGravityChanged(oldValue, cvar);
    });

    CVarWrapper gameGravityCVar = this->plugin->cvarManager->getCvar("st_g_gravity");
    if (gameGravityCVar.IsNull())
    {
        gameGravityCVar = this->plugin->cvarManager->registerCvar("st_g_gravity", "-650.0", "Current game gravity.");
    }
    this->gameGravity = std::make_unique<CVarWrapper>(gameGravityCVar);
    this->gameGravity->addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onGameGravityChanged(oldValue, cvar);
    });
}

void GameGravityComponent::onUnload()
{

}

void GameGravityComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Customize Game Gravity");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    ImGuiExtensions::PushDisableStyleIf(!isInFreeplay);

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

    ImGuiExtensions::PopDisableStyleIf(!isInFreeplay);

    ImGui::PopID();
}

float GameGravityComponent::getSvSoccarGameGravity()
{
    return (!this->svSoccarGameGravity || this->svSoccarGameGravity->IsNull()) ? 0.0f : this->svSoccarGameGravity->getFloatValue();
}

void GameGravityComponent::setSvSoccarGameGravity(float gravity)
{
    if (!this->svSoccarGameGravity || !this->svSoccarGameGravity->IsNull()) this->svSoccarGameGravity->setValue(gravity);
}

void GameGravityComponent::onSvSoccarGameGravityChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (this->getGameGravity() != this->getSvSoccarGameGravity())
    {
        this->setGameGravity(this->getSvSoccarGameGravity());
    }
}

float GameGravityComponent::getGameGravity()
{
    return (!this->gameGravity || this->gameGravity->IsNull()) ? 0.0f : this->gameGravity->getFloatValue();
}

void GameGravityComponent::setGameGravity(float gravity)
{
    if (!this->gameGravity || !this->gameGravity->IsNull()) this->gameGravity->setValue(gravity);
}

void GameGravityComponent::onGameGravityChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (this->getSvSoccarGameGravity() != this->getGameGravity())
    {
        this->setSvSoccarGameGravity(this->getGameGravity());
    }
}
