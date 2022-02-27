#include "AirDribbleHoopsMapToolsComponent.h"
#include "AirDribbleHoopsAutoSplitterComponent.h"

AirDribbleHoopsMapToolsComponent::AirDribbleHoopsMapToolsComponent(NetcodePlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<AirDribbleHoopsAutoSplitterComponent>(plugin),
                            "Air Dribble Hoops", "airhoops", 0)
{

}

void AirDribbleHoopsMapToolsComponent::resetMap()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("servertravel ?");
}

void AirDribbleHoopsMapToolsComponent::checkpoint(int checkpoint)
{

}
