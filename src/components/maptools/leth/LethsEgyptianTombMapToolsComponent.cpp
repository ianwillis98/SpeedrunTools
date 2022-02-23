#include "LethsEgyptianTombMapToolsComponent.h"
#include "LethsEgyptianTombAutoSplitterComponent.h"

LethsEgyptianTombMapToolsComponent::LethsEgyptianTombMapToolsComponent(NetcodePlugin* plugin)
    : MapToolsComponent(plugin, std::make_shared<LethsEgyptianTombAutoSplitterComponent>(plugin),
        "Leth's Egyptian Tomb", "lethstomb", 0)
{

}

void LethsEgyptianTombMapToolsComponent::resetMap()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("servertravel ?");
}

void LethsEgyptianTombMapToolsComponent::checkpoint(int checkpoint)
{

}