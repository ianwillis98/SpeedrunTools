#include "SpeedJumpRings2MapToolsComponent.h"
#include "SpeedJumpRings2AutoSplitterComponent.h"

SpeedJumpRings2MapToolsComponent::SpeedJumpRings2MapToolsComponent(NetcodePlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<SpeedJumpRings2AutoSplitterComponent>(plugin),
                            "Speed Jump Rings 2", "sjr2", 11)
{

}

void SpeedJumpRings2MapToolsComponent::resetMap()
{
    this->mapToolsModel.resetPlayers();
}

void SpeedJumpRings2MapToolsComponent::checkpoint(int checkpoint)
{
    this->kismetModel.setIntValue("Level", checkpoint);
    if (checkpoint == 1)
    {
        this->mapToolsModel.resetPlayers();
    }
    else if (checkpoint == 2)
    {
        this->mapToolsModel.setCarState(Vector(-3426.04f, -28281.11f, 6408.91f), Rotator(-100, -6352, 0));
    }
    else if (checkpoint == 3)
    {
        this->mapToolsModel.setCarState(Vector(13492.1f, -40001.82f, 6408.91f), Rotator(-100, 544, 0));
    }
    else if (checkpoint == 4)
    {
        this->mapToolsModel.setCarState(Vector(37018.63f, -32405.27f, 6408.91f), Rotator(-100, 16175, 0));
    }
    else if (checkpoint == 5)
    {
        this->mapToolsModel.setCarState(Vector(42738.64, -6853.12f, 6408.91f), Rotator(-100, 19100, 0));
    }
    else if (checkpoint == 6)
    {
        this->mapToolsModel.setCarState(Vector(35231.16, 14098.31, 6408.91f), Rotator(-100, 25196, 0));
    }
    else if (checkpoint == 7)
    {
        this->mapToolsModel.setCarState(Vector(16083.3, 33961.22f, 6408.91f), Rotator(-100, 25196, 0));
    }
    else if (checkpoint == 8)
    {
        this->mapToolsModel.setCarState(Vector(4455.69f, 53617.48f, 6408.91f), Rotator(-100, -29508, 0));
    }
    else if (checkpoint == 9)
    {
        this->mapToolsModel.setCarState(Vector(-5744.28f, 37085.43f, 6408.91f), Rotator(-100, -25604, 0));
    }
    else if (checkpoint == 10)
    {
        this->mapToolsModel.setCarState(Vector(-19878.63f, 27680.63f, 6408.91f), Rotator(-100, -19440, 0));
    }
    else if (checkpoint == 11)
    {
        this->mapToolsModel.setCarState(Vector(-31937.28, 3628.14f, 6408.91f), Rotator(-100, -16368, 0));
    }
}
