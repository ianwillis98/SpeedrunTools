#include "SpeedJumpRings3MapToolsComponent.h"
#include "SpeedJumpRings3AutoSplitterComponent.h"

SpeedJumpRings3MapToolsComponent::SpeedJumpRings3MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<SpeedJumpRings3AutoSplitterComponent>(plugin),
                            "Speed Jump Rings 3", "sjr3", 14)
{

}

void SpeedJumpRings3MapToolsComponent::resetMap()
{
    std::vector<KismetSequenceVariable> vars = this->mapToolsModel.getKismetVars();
    for (auto &var : vars)
    {
        if (var.getName() == "Level")
        {
            var.setIntValue(1);
            var.updateMainSequenceValue();
        }
    }
    this->mapToolsModel.setCarState(Vector(-6793, -8487, 719), Rotator(0, -16386, 0), Vector(0, 0, 0), Vector(0, 0, 0), 1.0f);
}

void SpeedJumpRings3MapToolsComponent::checkpoint(int checkpoint)
{
    if (checkpoint == 1)
    {
        this->resetMap();
        return;
    }

    std::vector<KismetSequenceVariable> vars = this->mapToolsModel.getKismetVars();
    for (auto &var : vars)
    {
        if (var.getName() == "Level")
        {
            var.setIntValue(checkpoint);
            var.updateMainSequenceValue();
        }
    }
    this->mapToolsModel.resetPlayers();

}
