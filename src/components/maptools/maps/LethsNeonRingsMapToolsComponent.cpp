#include "LethsNeonRingsMapToolsComponent.h"
#include "../autosplitter/runs/LethsNeonRingsAutoSplitterComponent.h"

LethsNeonRingsMapToolsComponent::LethsNeonRingsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<LethsNeonRingsAutoSplitterComponent>(plugin),
                            "Leth's Neon Rings", "lethsneon", 20)
{

}

void LethsNeonRingsMapToolsComponent::resetMap()
{
    std::vector<KismetSequenceVariable> kismetVars = this->mapToolsModel.getKismetVars();
    for (auto &var : kismetVars)
    {
        if (var.getName() == "Deaths")
        {
            var.setIntValue(0);
            var.updateMainSequenceValue();
        }
        if (var.getName() == "Level")
        {
            var.setIntValue(0);
            var.updateMainSequenceValue();
        }
        if (var.getName() == "Seconds")
        {
            var.setIntValue(0);
            var.updateMainSequenceValue();
        }
        if (var.getName() == "Timing")
        {
            var.setBoolValue(false);
            var.updateMainSequenceValue();
        }
    }
    this->mapToolsModel.resetPlayers();
}

void LethsNeonRingsMapToolsComponent::checkpoint(int checkpoint)
{
    std::vector<KismetSequenceVariable> kismetVars = this->mapToolsModel.getKismetVars();
    for (auto &var : kismetVars)
    {
        if (var.getName() == "Level")
        {
            var.setIntValue(checkpoint);
            var.updateMainSequenceValue();
        }
    }
    this->mapToolsModel.resetPlayers();
}
