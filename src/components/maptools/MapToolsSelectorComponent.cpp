#include "MapToolsSelectorComponent.h"
#include "tutorial/TutorialBasicMapToolsComponent.h"
#include "tutorial/TutorialAdvancedMapToolsComponent.h"
#include "leth/LethsNeonRingsMapToolsComponent.h"
#include "panic/PanicsAirRaceBeachMapToolsComponent.h"
#include "speedjump/rings/SpeedJumpRings1MapToolsComponent.h"
#include "speedjump/rings/SpeedJumpRings2MapToolsComponent.h"
#include "speedjump/rings/SpeedJumpRings3MapToolsComponent.h"
#include "leth/LethsGiantRingsMapToolsComponent.h"
#include "speedjump/trials/SpeedJumpTrials1MapToolsComponent.h"
#include "airdribble/AirDribbleHoopsMapToolsComponent.h"
#include "dribble/Dribble2OverhaulMapToolsComponent.h"
#include "leth/LethsEgyptianTombMapToolsComponent.h"
#include "minigolf/MinigolfMapToolsComponent.h"
#include "../../external/ocornut/imgui/imgui_searchablecombo.h"

MapToolsSelectorComponent::MapToolsSelectorComponent(NetcodePlugin *plugin)
        : PluginComponentBase(plugin),
          maps(),
          selectedMapIndex(0)
{
    this->maps.push_back(std::make_unique<TutorialBasicMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<TutorialAdvancedMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<PanicsAirRaceBeachMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<LethsNeonRingsMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<LethsGiantRingsMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<AirDribbleHoopsMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings1MapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings2MapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<SpeedJumpRings3MapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<Dribble2OverhaulMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<LethsEgyptianTombMapToolsComponent>(plugin));
    this->maps.push_back(std::make_unique<MinigolfMapToolsComponent>(plugin));
    //this->maps.push_back(std::make_unique<SpeedJumpTrials1MapToolsComponent>(plugin));

    this->mapNames = {};
    this->mapNames.reserve(this->maps.size());
    for (const auto& map : maps) 
    {
        this->mapNames.push_back(map->getMapName());
    }

    this->plugin->cvarManager->registerNotifier("speedrun_maptools_global_reset", [this](const std::vector<std::string>& commands) {
        for (int i = 0; i < this->maps.size(); i++)
        {
            if (i == this->selectedMapIndex)
            {
                this->plugin->cvarManager->executeCommand("speedrun_maptools_" + this->maps.at(i)->getCvar() + "_reset");
                return;
            }
        }
        }, "", PERMISSION_PAUSEMENU_CLOSED);
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

    if (ImGui::SearchableCombo("map", &this->selectedMapIndex, mapNames, "", "")) {
        for (int i = 0; i < this->maps.size(); i++)
        {
            if (this->selectedMapIndex != i)
                this->maps.at(i)->disableAutoSplitter();
        }
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
