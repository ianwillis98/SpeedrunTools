#include <renderingtools/objects/Cube.h>
#include "ExperimentalComponent.h"

ExperimentalComponent::ExperimentalComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponentBase(plugin)
{

}

void ExperimentalComponent::render()
{
}

void ExperimentalComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    Vector center(0, 0, 0);
    RT::Cube cube(center, 150);

    cube.Draw(canvasWrapper);
}

void ExperimentalComponent::onEvent(const std::string &eventName, bool post, void *params)
{
}


