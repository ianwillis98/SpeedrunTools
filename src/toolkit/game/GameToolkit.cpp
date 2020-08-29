#include <cmath>
#include "GameToolkit.h"

GameToolkit::GameToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin, GameGravityComponent &gameGravityComponent,
                         GameSpeedComponent &gameSpeedComponent)
        : PluginToolkit(plugin), gameGravityComponent(gameGravityComponent), gameSpeedComponent(gameSpeedComponent)
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
