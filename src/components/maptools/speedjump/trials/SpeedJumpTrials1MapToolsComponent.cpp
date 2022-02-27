#include "SpeedJumpTrials1MapToolsComponent.h"
#include "SpeedJumpTrials1AutoSplitterComponent.h"

SpeedJumpTrials1MapToolsComponent::SpeedJumpTrials1MapToolsComponent(NetcodePlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<SpeedJumpTrials1AutoSplitterComponent>(plugin),
                            "Speed Jump Trials 1", "sjt1", 10)
{

}
void SpeedJumpTrials1MapToolsComponent::resetMap()
{
    this->kismetModel.setBoolValue("Reset", true);
    this->mapToolsModel.resetPlayers();
}

void SpeedJumpTrials1MapToolsComponent::checkpoint(int checkpoint)
{
    if (checkpoint == 1)
    {
        this->resetMap();
    }
    else if (2 <= checkpoint && checkpoint <= 10)
    {
        this->kismetModel.setBoolValue("Reset", false);
        this->kismetModel.setIntValue("Level", checkpoint);
        this->mapToolsModel.resetPlayers();
    }
}
