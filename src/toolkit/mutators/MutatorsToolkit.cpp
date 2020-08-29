#include "MutatorsToolkit.h"

MutatorsToolkit::MutatorsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), gameGravityComponent(plugin), gameSpeedComponent(plugin)
{

}

std::string MutatorsToolkit::title()
{
    return "Mutators";
}

void MutatorsToolkit::onLoad()
{
    this->gameGravityComponent.onLoad();
    this->gameSpeedComponent.onLoad();
}

void MutatorsToolkit::onUnload()
{
    this->gameGravityComponent.onUnload();
    this->gameSpeedComponent.onUnload();
}

void MutatorsToolkit::render()
{
    ImGui::Spacing();

    this->gameGravityComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->gameSpeedComponent.render();

    ImGui::Spacing();
}
