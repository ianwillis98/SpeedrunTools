#include "Dribble2OverhaulMapToolsComponent.h"
#include "Dribble2OverhaulAutoSplitterComponent.h"

Dribble2OverhaulMapToolsComponent::Dribble2OverhaulMapToolsComponent(NetcodePlugin* plugin)
    : MapToolsComponent(plugin, std::make_shared<Dribble2OverhaulAutoSplitterComponent>(plugin),
        "Dribble Challenge 2 Overhaul", "dribble2overhaul", 0)
{

}

void Dribble2OverhaulMapToolsComponent::resetMap()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("servertravel ?");
}

void Dribble2OverhaulMapToolsComponent::checkpoint(int checkpoint)
{

}