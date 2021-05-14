#include "PanicsAirRaceBeachMapToolsComponent.h"
#include "../autosplitter/runs/PanicsAirRaceBeachAutoSplitterComponent.h"

PanicsAirRaceBeachMapToolsComponent::PanicsAirRaceBeachMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<PanicsAirRaceBeachAutoSplitterComponent>(plugin),
                            "Panic's Air Race Beach", "panicsbeach", 11)
{

}


void PanicsAirRaceBeachMapToolsComponent::resetMap()
{
    this->mapToolsModel.resetPlayers();
}

void PanicsAirRaceBeachMapToolsComponent::checkpoint(int checkpoint)
{
    if (checkpoint == 1)
    {
        this->setCheckpointAndCount(0, 30);
        this->mapToolsModel.setCarState(Vector(11429.07f, -25964.96f, 50.0f), Rotator(-100, 3968, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 2)
    {
        this->setCheckpointAndCount(1, 39);
        this->mapToolsModel.setCarState(Vector(7217.72f, -16505.14, 0.0f), Rotator(-100, 12896, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 3)
    {
        this->setCheckpointAndCount(2, 61);
        this->mapToolsModel.setCarState(Vector(1581.56f, 793.88, 20.0f), Rotator(-100, -16640, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 4)
    {
        this->setCheckpointAndCount(3, 70);
        this->mapToolsModel.setCarState(Vector(-4065.12f, -12098.14, 70.0f), Rotator(-100, 19840, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 5)
    {
        this->setCheckpointAndCount(4, 76);
        this->mapToolsModel.setCarState(Vector(-6041.78f, 3165.77f, 0.0f), Rotator(-100, 23648, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 6)
    {
        this->setCheckpointAndCount(5, 84);
        this->mapToolsModel.setCarState(Vector(10414.92f, 5010.13f, 0.0f), Rotator(-100, -8064, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 7)
    {
        this->setCheckpointAndCount(6, 91);
        this->mapToolsModel.setCarState(Vector(17088.68f, 9103.98f, 110.0f), Rotator(-100, 26048, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 8)
    {
        this->setCheckpointAndCount(7, 118);
        this->mapToolsModel.setCarState(Vector(12386.14f, 15565.47f, 110.0f), Rotator(-100, -4128, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 9)
    {
        this->setCheckpointAndCount(8, 126);
        this->mapToolsModel.setCarState(Vector(10192.17f, 21147.19f, 0.0f), Rotator(-100, 21472, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 10)
    {
        this->setCheckpointAndCount(9, 155);
        this->mapToolsModel.setCarState(Vector(-868.84, 13827.73f, 0.0f), Rotator(-100, 31648, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 11)
    {
        this->setCheckpointAndCount(10, 172);
        this->mapToolsModel.setCarState(Vector(-13317.81, 7834.1f, 0.0f), Rotator(-100, -21824, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
}

void PanicsAirRaceBeachMapToolsComponent::setCheckpointAndCount(int checkpoint, int count)
{
    std::vector<KismetSequenceVariable> kismetVars = this->mapToolsModel.getKismetVars();
    for (auto &var : kismetVars)
    {
        if (var.getName() == "Player1CPCount")
        {
            var.setIntValue(checkpoint);
            var.updateMainSequenceValue();
        }
        if (var.getName() == "Player1Count")
        {
            var.setIntValue(count);
            var.updateMainSequenceValue();
        }
    }
}
