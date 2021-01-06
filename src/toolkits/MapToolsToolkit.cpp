#include "MapToolsToolkit.h"

MapToolsToolkit::MapToolsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin),
          mapToolsComponent(plugin)
{

}

std::string MapToolsToolkit::title()
{
    return "Map Tools";
}

void MapToolsToolkit::onLoad()
{
    this->mapToolsComponent.onLoad();
}

void MapToolsToolkit::render()
{
    this->mapToolsComponent.render();
}

void MapToolsToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->mapToolsComponent.onEvent(eventName, post, params);
}
