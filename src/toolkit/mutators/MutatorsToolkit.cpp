#include "MutatorsToolkit.h"

MutatorsToolkit::MutatorsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), gameGravityComponent(plugin), gameSpeedComponent(plugin), boostComponent(plugin), autoAirRollComponent(plugin)
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
    this->boostComponent.onLoad();
    this->autoAirRollComponent.onLoad();
}

void MutatorsToolkit::onUnload()
{
    this->gameGravityComponent.onUnload();
    this->gameSpeedComponent.onUnload();
    this->boostComponent.onUnload();
    this->autoAirRollComponent.onUnload();
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
    ImGui::Separator();
    ImGui::Spacing();

    this->boostComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->autoAirRollComponent.render();

    ImGui::Spacing();
}
