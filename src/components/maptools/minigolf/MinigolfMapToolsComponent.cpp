#include "MinigolfMapToolsComponent.h"
#include "MinigolfAutoSplitterComponent.h"

MinigolfMapToolsComponent::MinigolfMapToolsComponent(NetcodePlugin* plugin)
    : MapToolsComponent(plugin, std::make_shared<MinigolfAutoSplitterComponent>(plugin),
        "Minigolf", "minigolf", 0)
{

}

void MinigolfMapToolsComponent::resetMap()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("servertravel ?");
}

void MinigolfMapToolsComponent::checkpoint(int checkpoint)
{

}
