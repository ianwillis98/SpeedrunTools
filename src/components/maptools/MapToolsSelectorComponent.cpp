#include "MapToolsSelectorComponent.h"
#include "maps/tutorial/TutorialBasicMapToolsComponent.h"
#include "maps/tutorial/TutorialAdvancedMapToolsComponent.h"
#include "maps/LethsNeonRingsMapToolsComponent.h"
#include "maps/PanicsAirRaceBeachMapToolsComponent.h"
#include "maps/speedjump/SpeedJumpRings1MapToolsComponent.h"
#include "maps/speedjump/SpeedJumpRings2MapToolsComponent.h"

MapToolsSelectorComponent::MapToolsSelectorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          maps(),
          selectedMapIndex(0)
{
    this->maps.push_back(std::make_unique<TutorialBasicMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<TutorialAdvancedMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<LethsNeonRingsMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<PanicsAirRaceBeachMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings1MapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings2MapToolsComponent>(plugin));
}

void MapToolsSelectorComponent::render()
{
    ImGui::Text("Choose a map:");
    ImGui::Spacing();

    if (ImGui::BeginCombo("map", this->maps.at(this->selectedMapIndex)->getMapName().c_str()))
    {
        for (int i = 0; i < this->maps.size(); i++)
        {
            bool isSelected = this->selectedMapIndex == i;
            if (ImGui::Selectable(this->maps.at(i)->getMapName().c_str(), isSelected))
                this->selectedMapIndex = i;
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGuiExtensions::BigSeparator();

    this->maps.at(selectedMapIndex)->render();
}

void MapToolsSelectorComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    for (auto &map : this->maps)
    {
        map->onEvent(eventName, post, params);
    }
}
