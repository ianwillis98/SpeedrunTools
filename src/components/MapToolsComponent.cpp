#include "MapToolsComponent.h"

MapToolsComponent::MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), currentMapName()
{

}

std::string MapToolsComponent::title()
{
    return "Map Tools";
}

void MapToolsComponent::onLoad()
{

}

void MapToolsComponent::render()
{
    ImGui::Text("Current map: %s", this->currentMapName.c_str());
}

void MapToolsComponent::onEvent(std::string eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        this->currentMapName = this->plugin->gameWrapper->GetCurrentMap();
    }
}
