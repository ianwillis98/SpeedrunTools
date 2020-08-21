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
            this->onSvSoccarGameGravityCVarChanged(oldValue, cvar);
        });
    }

    CVarWrapper gameGravityCVar = this->plugin->cvarManager->registerCvar("st_g_gravity", "-650.0", "Current game gravity.");
    gameGravityCVar.bindTo(this->gameGravity);
    gameGravityCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onGameGravityCVarChanged(oldValue, cvar);
    });

    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    if (!svSoccarGameSpeedCVar.IsNull())
    {
        svSoccarGameSpeedCVar.bindTo(this->svSoccarGameSpeed);
        svSoccarGameSpeedCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
            this->onSvSoccarGameSpeedCVarChanged(oldValue, cvar);
        });
    }

    CVarWrapper gameSpeedCVar = this->plugin->cvarManager->registerCvar("st_g_speed", "1.0", "Current game speed.");
    gameSpeedCVar.bindTo(this->gameSpeed);
    gameSpeedCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onGameSpeedCVarChanged(oldValue, cvar);
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

void GameToolkit::setSvSoccarGameGravityCVar(float gravity)
{
    CVarWrapper svSoccarGameGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    if (svSoccarGameGravityCVar.IsNull()) return;

    svSoccarGameGravityCVar.setValue(gravity);
}

void GameToolkit::onSvSoccarGameGravityCVarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (*this->gameGravity != *this->svSoccarGameGravity)
    {
        this->setGameGravityCVar(*this->svSoccarGameGravity);
    }
}

void GameToolkit::setGameGravityCVar(float gravity)
{
    CVarWrapper gameGravityCVar = this->plugin->cvarManager->getCvar("st_g_gravity");
    if (gameGravityCVar.IsNull()) return;

    gameGravityCVar.setValue(gravity);
}

void GameToolkit::onGameGravityCVarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (*this->svSoccarGameGravity != *this->gameGravity)
    {
        this->setSvSoccarGameGravityCVar(*this->gameGravity);
    }
}

void GameToolkit::setSvSoccarGameSpeedCVar(float speed)
{
    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    if (svSoccarGameSpeedCVar.IsNull()) return;

    svSoccarGameSpeedCVar.setValue(speed);
}

void GameToolkit::onSvSoccarGameSpeedCVarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (*this->gameSpeed != *this->svSoccarGameSpeed)
    {
        this->setGameSpeedCVar(*this->svSoccarGameSpeed);
    }
}

void GameToolkit::setGameSpeedCVar(float speed)
{
    CVarWrapper gameSpeedCVar = this->plugin->cvarManager->getCvar("st_g_speed");
    if (gameSpeedCVar.IsNull()) return;

    gameSpeedCVar.setValue(speed);
}

void GameToolkit::onGameSpeedCVarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (*this->svSoccarGameSpeed != *this->gameSpeed)
    {
        this->setSvSoccarGameSpeedCVar(*this->gameSpeed);
    }
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
            this->setGameGravityCVar(*this->gameGravity);
        });
    }

    if (ImGui::Button("Default (-650.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravityCVar(-650.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero (-0.001)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravityCVar(-0.001f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Inverted (650.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameGravityCVar(650.0f);
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
            this->setGameSpeedCVar(*this->gameSpeed);
        });
    }

    if (ImGui::Button("Default (1.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeedCVar(1.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Half (0.5)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeedCVar(0.5f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Double (2.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setGameSpeedCVar(2.0f);
        });
    }

    if (!isInFreeplay)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}
