#include "LethsGiantRingsMapToolsComponent.h"
#include "LethsGiantRingsAutoSplitterComponent.h"

LethsGiantRingsMapToolsComponent::LethsGiantRingsMapToolsComponent(NetcodePlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<LethsGiantRingsAutoSplitterComponent>(plugin),
                            "Leth's Giant Rings", "lethsgiant", 20)
{

}

void LethsGiantRingsMapToolsComponent::resetMap()
{
    this->kismetModel.setBoolValue("Timing", false);
    this->kismetModel.setIntValue("Level", 1);
    this->kismetModel.setIntValue("Deaths", 0);
    this->kismetModel.setIntValue("Seconds", 0);
    this->mapToolsModel.resetPlayers();
}

void LethsGiantRingsMapToolsComponent::checkpoint(int checkpoint)
{
    this->kismetModel.setIntValue("Level", checkpoint);
    this->mapToolsModel.resetPlayers();
}
