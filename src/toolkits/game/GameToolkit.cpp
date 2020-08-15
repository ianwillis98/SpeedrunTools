#include <cmath>
#include "GameToolkit.h"

GameToolkit::GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{
    this->svSoccarGameGravity = std::make_shared<float>();
    this->svSoccarGameSpeed = std::make_shared<float>();
}

std::string GameToolkit::title()
{
    return "Game Settings";
}

void GameToolkit::onLoad()
{
    this->plugin->cvarManager->getCvar("sv_soccar_gravity").bindTo(this->svSoccarGameGravity);
    this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").bindTo(this->svSoccarGameSpeed);
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

void GameToolkit::setGameGravity(float gravity)
{
    CVarWrapper svSoccarGameGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    if (svSoccarGameGravityCVar.IsNull()) return;

    gravity = std::fmax(-5000.0f, std::fmin(5000.0f, gravity));
    gravity = gravity == 0 ? -0.00001f : gravity; // setting it directly to zero does nothing

    svSoccarGameGravityCVar.setValue(gravity);
}

void GameToolkit::setGameSpeed(float speed)
{
    CVarWrapper svSoccarGameSpeedCVar = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed");
    if (svSoccarGameSpeedCVar.IsNull()) return;

    speed = std::fmax(0.05f, std::fmin(5.0f, speed));

    svSoccarGameSpeedCVar.setValue(speed);
}

void GameToolkit::renderGameGravityView()
{
    ImGui::Text("Customize Game Gravity");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = isInFreeplay ? ImGui::GetStyle().Colors[ImGuiCol_TextDisabled] : ImGui::GetStyle().Colors[ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    if (ImGui::SliderFloat("Game Gravity", this->svSoccarGameGravity.get(), -5000.0f, 5000.0f, "%.3f"))
    {
        this->setGameGravity(*this->svSoccarGameGravity);
    }

    if (ImGui::Button("Default (-650.0)"))
    {
        this->setGameGravity(-650.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero Gravity (0.0)"))
    {
        this->setGameGravity(0.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Inverted (650.0)"))
    {
        this->setGameGravity(650.0f);
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

    ImVec4 color = isInFreeplay ? ImGui::GetStyle().Colors[ImGuiCol_TextDisabled] : ImGui::GetStyle().Colors[ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    if (ImGui::SliderFloat("Game Speed", this->svSoccarGameSpeed.get(), 0.05f, 5.0f, "%.3f"))
    {
        this->setGameSpeed(*this->svSoccarGameSpeed);
    }

    if (ImGui::Button("Default (1.0)"))
    {
        this->setGameSpeed(1.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Half (0.5)"))
    {
        this->setGameSpeed(0.5f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Double (2.0)"))
    {
        this->setGameSpeed(2.0f);
    }

    if (!isInFreeplay)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}
