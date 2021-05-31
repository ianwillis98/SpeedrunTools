#include "SpeedJumpRings2MapToolsComponent.h"
#include "SpeedJumpRings2AutoSplitterComponent.h"

SpeedJumpRings2MapToolsComponent::SpeedJumpRings2MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<SpeedJumpRings2AutoSplitterComponent>(plugin),
                            "Speed Jump Rings 2", "sjr2", 0)
{

}

void SpeedJumpRings2MapToolsComponent::resetMap()
{
    this->mapToolsModel.resetPlayers();
}

void SpeedJumpRings2MapToolsComponent::checkpoint(int checkpoint)
{

}
