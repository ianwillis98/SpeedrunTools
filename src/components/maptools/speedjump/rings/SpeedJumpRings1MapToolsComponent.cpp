#include "SpeedJumpRings1MapToolsComponent.h"
#include "SpeedJumpRings1AutoSplitterComponent.h"

SpeedJumpRings1MapToolsComponent::SpeedJumpRings1MapToolsComponent(NetcodePlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<SpeedJumpRings1AutoSplitterComponent>(plugin),
                            "Speed Jump Rings 1", "sjr1", 0)
{

}

void SpeedJumpRings1MapToolsComponent::resetMap()
{
    this->mapToolsModel.resetPlayers();
}

void SpeedJumpRings1MapToolsComponent::checkpoint(int checkpoint)
{

}
