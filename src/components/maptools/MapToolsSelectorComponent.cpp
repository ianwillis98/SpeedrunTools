#include "MapToolsSelectorComponent.h"
#include "tutorial/TutorialBasicMapToolsComponent.h"
#include "tutorial/TutorialAdvancedMapToolsComponent.h"
#include "leth/LethsNeonRingsMapToolsComponent.h"
#include "panic/PanicsAirRaceBeachMapToolsComponent.h"
#include "speedjump/rings/SpeedJumpRings1MapToolsComponent.h"
#include "speedjump/rings/SpeedJumpRings2MapToolsComponent.h"
#include "speedjump/rings/SpeedJumpRings3MapToolsComponent.h"
#include "leth/LethsGiantRingsMapToolsComponent.h"

MapToolsSelectorComponent::MapToolsSelectorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          maps(),
          selectedMapIndex(0)
{
    this->maps.push_back(std::make_unique<TutorialBasicMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<TutorialAdvancedMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<LethsNeonRingsMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<LethsGiantRingsMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<PanicsAirRaceBeachMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings1MapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings2MapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings3MapToolsComponent>(plugin));
}

void MapToolsSelectorComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    for (auto &map : this->maps)
    {
        map->onEvent(eventName, post, params);
    }
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

void MapToolsSelectorComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
    for (int i = 0; i < this->maps.size(); i++)
    {
        if (i == this->selectedMapIndex)
        {
            this->maps.at(i)->renderCanvas(canvasWrapper);
        }
    }
}
