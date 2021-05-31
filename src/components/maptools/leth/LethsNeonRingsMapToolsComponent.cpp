#include "LethsNeonRingsMapToolsComponent.h"
#include "LethsNeonRingsAutoSplitterComponent.h"

LethsNeonRingsMapToolsComponent::LethsNeonRingsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<LethsNeonRingsAutoSplitterComponent>(plugin),
                            "Leth's Neon Rings", "lethsneon", 20)
{

}

void LethsNeonRingsMapToolsComponent::resetMap()
{
    this->kismetModel.setBoolValue("Timing", false);
    this->kismetModel.setIntValue("Level", 1);
    this->kismetModel.setIntValue("Deaths", 0);
    this->kismetModel.setIntValue("Seconds", 0);
    this->mapToolsModel.resetPlayers();
}

void LethsNeonRingsMapToolsComponent::checkpoint(int checkpoint)
{
    this->kismetModel.setIntValue("Level", checkpoint);
    this->mapToolsModel.resetPlayers();
}
