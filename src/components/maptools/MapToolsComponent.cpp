#include "MapToolsComponent.h"
#include "maps/TutorialBasicMapTools.h"
#include "maps/TutorialAdvancedMapTools.h"

MapToolsComponent::MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          supportedMaps()
{
    this->supportedMaps.emplace_back("Tutorial Basic", std::make_unique<TutorialBasicMapTools>(plugin));
    this->supportedMaps.emplace_back("Tutorial Advanced", std::make_unique<TutorialAdvancedMapTools>(plugin));
}

void MapToolsComponent::onLoad()
{
    for (auto &supportedMap : this->supportedMaps)
    {
        supportedMap.mapTools->onLoad();
    }
}

void MapToolsComponent::render()
{
    std::vector<const char *> mapNames;
    for (auto &supportedMap : this->supportedMaps)
    {
        mapNames.push_back(supportedMap.mapName.c_str());
    }
    static int comboIndex = 0;
    ImGui::Combo("map", &comboIndex, mapNames.data(), mapNames.size());

    ImGuiExtensions::BigSeparator();

    this->supportedMaps.at(comboIndex).mapTools->render();
}

void MapToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {

    }
}
