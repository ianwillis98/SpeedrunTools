#include "SpeedJumpRings3MapToolsComponent.h"
#include "SpeedJumpRings3AutoSplitterComponent.h"

SpeedJumpRings3MapToolsComponent::SpeedJumpRings3MapToolsComponent(NetcodePlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<SpeedJumpRings3AutoSplitterComponent>(plugin),
                            "Speed Jump Rings 3", "sjr3", 14)
{

}

void SpeedJumpRings3MapToolsComponent::resetMap()
{
    this->kismetModel.setIntValue("Level", 1);
    this->mapToolsModel.setCarState(Vector(-6793, -8487, 719), Rotator(0, -16386, 0));
}

void SpeedJumpRings3MapToolsComponent::checkpoint(int checkpoint)
{
    if (checkpoint == 1)
    {
        this->resetMap();
        return;
    }

    this->kismetModel.setIntValue("Level", checkpoint);
    this->mapToolsModel.resetPlayers();
}
