#include "GeneralToolsToolkit.h"

GeneralToolsToolkit::GeneralToolsToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin), generalToolsComponent(plugin)
{

}

std::string GeneralToolsToolkit::title()
{
    return "General Tools";
}

void GeneralToolsToolkit::onLoad()
{
    this->generalToolsComponent.onLoad();
}

void GeneralToolsToolkit::render()
{
    this->generalToolsComponent.render();
}

void GeneralToolsToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->generalToolsComponent.onEvent(eventName, post, params);
}
