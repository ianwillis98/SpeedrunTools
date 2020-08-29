#include "GameSpeedComponent.h"

GameSpeedComponent::GameSpeedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), svSoccarGameSpeed(nullptr), gameSpeed(nullptr)
{

}

void GameSpeedComponent::onLoad()
{
    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    if (svSoccarGameSpeedCVar.IsNull())
    {
        this->plugin->cvarManager->log("sv_soccar_gamespeed was null. Custom game speed won't work.");
    }
    this->svSoccarGameSpeed = std::make_unique<CVarWrapper>(svSoccarGameSpeedCVar);
    this->svSoccarGameSpeed->addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onSvSoccarGameSpeedChanged(oldValue, cvar);
    });

    CVarWrapper gameSpeedCVar = this->plugin->cvarManager->getCvar("st_g_speed");
    if (gameSpeedCVar.IsNull())
    {
        gameSpeedCVar = this->plugin->cvarManager->registerCvar("st_g_Speed", "1.0", "Current game speed.");
    }
    this->gameSpeed = std::make_unique<CVarWrapper>(gameSpeedCVar);
    this->gameSpeed->addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onGameSpeedChanged(oldValue, cvar);
    });
}

void GameSpeedComponent::onUnload()
{

}

void GameSpeedComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Customize Game Speed");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

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
    if (ImGui::Button("Half (0.5)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeed(0.5f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Double (2.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeed(2.0f);
        });
    }

    if (!isInFreeplay)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }

    ImGui::PopID();
}

float GameSpeedComponent::getSvSoccarGameSpeed()
{
    return (!this->svSoccarGameSpeed || this->svSoccarGameSpeed->IsNull()) ? 0.0f : this->svSoccarGameSpeed->getFloatValue();
}

void GameSpeedComponent::setSvSoccarGameSpeed(float speed)
{
    if (!this->svSoccarGameSpeed || !this->svSoccarGameSpeed->IsNull()) this->svSoccarGameSpeed->setValue(speed);
}

void GameSpeedComponent::onSvSoccarGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (this->getGameSpeed() != this->getSvSoccarGameSpeed())
    {
        this->setGameSpeed(this->getSvSoccarGameSpeed());
    }
}

float GameSpeedComponent::getGameSpeed()
{
    return (!this->gameSpeed || this->gameSpeed->IsNull()) ? 0.0f : this->gameSpeed->getFloatValue();
}

void GameSpeedComponent::setGameSpeed(float speed)
{
    if (!this->gameSpeed || !this->gameSpeed->IsNull()) this->gameSpeed->setValue(speed);
}

void GameSpeedComponent::onGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (this->getSvSoccarGameSpeed() != this->getGameSpeed())
    {
        this->setSvSoccarGameSpeed(this->getGameSpeed());
    }
}
