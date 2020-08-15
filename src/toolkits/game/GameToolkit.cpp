#include <cmath>
#include "GameToolkit.h"

GameToolkit::GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{
    this->gameGravity = -650.0f;
    this->gameSpeed = std::make_shared<float>(1.0f);
}

std::string GameToolkit::title()
{
    return "Game Settings";
}

void GameToolkit::onLoad()
{
    CVarWrapper gravityCVar = this->plugin->cvarManager->registerCvar("fpt_g_gravity", "-650.0", "Current gravity of the game", true);
    gravityCVar.addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
        if (cvar.IsNull()) return;

        this->setGameGravity(cvar.getFloatValue());
    });

    this->plugin->cvarManager->registerCvar("fpt_g_speed", "1.0", "Current speed of the game", true, true, 0.05f, true, 5.0f, false)
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                if (cvar.IsNull()) return;

                this->setGameSpeed(cvar.getFloatValue());
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

void GameToolkit::setGameGravity(float gravity)
{
    CVarWrapper svSoccarGravityCVar = this->plugin->cvarManager->getCvar("sv_soccar_gravity");
    CVarWrapper gravityCVar = this->plugin->cvarManager->getCvar("fpt_g_gravity");
    if (svSoccarGravityCVar.IsNull() || gravityCVar.IsNull()) return;

    gravity = std::fmax(-5000.0f, std::fmin(5000.0f, gravity));
    gravity = gravity == 0 ? -0.00001f : gravity;
    this->gameGravity = gravity;

    //svSoccarGravityCVar.setValue(this->gameGravity);
    gravityCVar.setValue(this->gameGravity);
}

void GameToolkit::setGameSpeed(float speed)
{
    speed = std::fmax(0.05f, std::fmin(5.0f, speed));
    //this->gameSpeed = speed;

    // this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").setValue(gameSpeed);
}

void GameToolkit::renderGameGravityView()
{
    ImGui::Text("Customize Game Gravity");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = isInFreeplay ? ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]
                                : ImGui::GetStyle().Colors[ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    static float gravitySlider = -650.0f;
    ImGui::SliderFloat("Game Gravity", &gravitySlider, -5000.0f, 5000.0f, "%.3f");
    if (ImGui::Button(("Apply Game Gravity (" + std::to_string(gravitySlider) + ")").c_str()))
    {
        this->setGameGravity(gravitySlider);
    }
    ImGui::SameLine();
    float currentGravity = this->plugin->cvarManager->getCvar("sv_soccar_gravity").getFloatValue();
    ImGui::Text("(Current Game Gravity: %.3f)", currentGravity);
    if (ImGui::Button("Default Game Gravity (-650.0)"))
    {
        this->setGameGravity(-650.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Zero Game Gravity (0.0)"))
    {
        this->setGameGravity(0.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Invert Game Gravity (650.0)"))
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

    ImVec4 color = isInFreeplay ? ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]
                                : ImGui::GetStyle().Colors[ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    static float speedSlider = 1.0f;
    ImGui::SliderFloat("Game Speed", &speedSlider, 0.05f, 5.0f, "%.3f");
    if (ImGui::Button(("Apply Game Speed (" + std::to_string(speedSlider) + ")").c_str()))
    {
        this->setGameSpeed(speedSlider);
    }
    ImGui::SameLine();
    float currentSpeed = this->plugin->cvarManager->getCvar("sv_soccar_gamespeed").getFloatValue();
    ImGui::Text("(Current Game Speed: %.3f)", currentSpeed);
    if (ImGui::Button("Default Game Speed (1.0)"))
    {
        this->setGameSpeed(1.0f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Half Game Speed (0.5)"))
    {
        this->setGameSpeed(0.5f);
    }
    ImGui::SameLine();
    if (ImGui::Button("Double Game Speed (2.0)"))
    {
        this->setGameSpeed(2.0f);
    }

    if (!isInFreeplay)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}
