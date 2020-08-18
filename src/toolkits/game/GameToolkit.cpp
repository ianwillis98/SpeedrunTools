#include <cmath>
#include "GameToolkit.h"

GameToolkit::GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{
    this->svSoccarGameGravity = std::make_shared<float>();
    this->gameGravity = std::make_shared<float>();

    this->svSoccarGameSpeed = std::make_shared<float>();
    this->gameSpeed = std::make_shared<float>();
}

std::string GameToolkit::title()
{
    return "Game Settings";
}

void GameToolkit::onLoad()
{
    CVarWrapper svSoccarGameGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    if (!svSoccarGameGravityCVar.IsNull())
    {
        svSoccarGameGravityCVar.bindTo(this->svSoccarGameGravity);
        svSoccarGameGravityCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
            if (*this->gameGravity != *this->svSoccarGameGravity)
            {
                this->setGameGravity(*this->svSoccarGameGravity);
            }
        });
    }

    CVarWrapper gameGravityCVar = this->plugin->cvarManager->registerCvar("fpt_g_gravity", "-650.0", "Current game gravity.");
    gameGravityCVar.bindTo(this->gameGravity);
    gameGravityCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        if (*this->svSoccarGameGravity != *this->gameGravity)
        {
            this->setSvSoccarGameGravity(*this->gameGravity);
        }
    });

    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    if (!svSoccarGameSpeedCVar.IsNull())
    {
        svSoccarGameSpeedCVar.bindTo(this->svSoccarGameSpeed);
        svSoccarGameSpeedCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
            if (*this->gameSpeed != *this->svSoccarGameSpeed)
            {
                this->setGameSpeed(*this->svSoccarGameSpeed);
            }
        });
    }

    CVarWrapper gameSpeedCVar = this->plugin->cvarManager->registerCvar("fpt_g_speed", "1.0", "Current game speed.");
    gameSpeedCVar.bindTo(this->gameSpeed);
    gameSpeedCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        if (*this->svSoccarGameSpeed != *this->gameSpeed)
        {
            this->setSvSoccarGameSpeed(*this->gameSpeed);
        }
    });
}

void GameToolkit::onUnload()
{

}

void GameToolkit::render()
{
    ImGui::Spacing();

    this->renderGameGravityView();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->renderGameSpeedView();

    ImGui::Spacing();
}

void GameToolkit::setSvSoccarGameGravity(float gravity)
{
    CVarWrapper svSoccarGameGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    if (svSoccarGameGravityCVar.IsNull()) return;

    svSoccarGameGravityCVar.setValue(gravity);
}

void GameToolkit::setGameGravity(float gravity)
{
    CVarWrapper gameGravityCVar = this->plugin->cvarManager->getCvar("fpt_g_gravity");
    if (gameGravityCVar.IsNull()) return;

    gameGravityCVar.setValue(gravity);
}

void GameToolkit::setSvSoccarGameSpeed(float speed)
{
    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    if (svSoccarGameSpeedCVar.IsNull()) return;

    svSoccarGameSpeedCVar.setValue(speed);
}

void GameToolkit::setGameSpeed(float speed)
{
    CVarWrapper gameSpeedCVar = this->plugin->cvarManager->getCvar("fpt_g_speed");
    if (gameSpeedCVar.IsNull()) return;

    gameSpeedCVar.setValue(speed);
}

void GameToolkit::renderGameGravityView()
{
    ImGui::Text("Customize Game Gravity");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    if (ImGui::SliderFloat("Game Gravity", this->gameGravity.get(), -5000.0f, 5000.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravity(*this->gameGravity);
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

    if (!isInFreeplay)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}

void GameToolkit::renderGameSpeedView()
{
    ImGui::Text("Customize Game Speed");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    if (ImGui::SliderFloat("Game Speed", this->gameSpeed.get(), 0.05f, 5.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeed(*this->gameSpeed);
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
}
