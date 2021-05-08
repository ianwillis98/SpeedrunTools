#include "MapToolsComponent.h"
#include "maps/TutorialBasicComponent.h"
#include "maps/TutorialAdvancedComponent.h"
#include "maps/LethsNeonRingsMapToolsComponent.h"

MapToolsComponent::MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          supportedMaps(),
          comboIndex(0)
{
    this->supportedMaps.emplace_back("Tutorial Basic", std::make_unique<TutorialBasicComponent>(plugin));
    this->supportedMaps.emplace_back("Tutorial Advanced", std::make_unique<TutorialAdvancedComponent>(plugin));
    this->supportedMaps.emplace_back("Leths Neon Rings", std::make_unique<LethsNeonRingsMapToolsComponent>(plugin));
}

void MapToolsComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("MAP TOOLS");
    ImGui::Spacing();

    std::vector<const char *> mapNames;
    for (auto &supportedMap : this->supportedMaps)
    {
        mapNames.push_back(supportedMap.first.c_str());
    }
    ImGui::Combo("map", &comboIndex, mapNames.data(), mapNames.size());
    ImGuiExtensions::BigSeparator();

    this->supportedMaps.at(comboIndex).second->render();

    ImGui::PopID();
}

void MapToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    for (auto &supportedMap : this->supportedMaps)
    {
        supportedMap.second->onEvent(eventName, post, params);
    }
}
