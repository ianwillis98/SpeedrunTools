#include "GameToolkit.h"

GameToolkit::GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), gameGravityComponent(plugin), gameSpeedComponent(plugin)
{

}

std::string GameToolkit::title()
{
    return "Game Toolkit";
}

void GameToolkit::onLoad()
{
    this->gameGravityComponent.onLoad();
    this->gameSpeedComponent.onLoad();
}

void GameToolkit::onUnload()
{
    this->gameGravityComponent.onUnload();
    this->gameSpeedComponent.onUnload();
}

void GameToolkit::render()
{
    ImGui::Spacing();

    this->gameGravityComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->gameSpeedComponent.render();

    ImGui::Spacing();
}
