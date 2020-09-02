#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), liveSplitComponent(plugin)
{

}

std::string LiveSplitToolkit::title()
{
    return "LiveSplit";
}

void LiveSplitToolkit::onLoad()
{
    this->liveSplitComponent.onLoad();
}

void LiveSplitToolkit::onUnload()
{
    this->liveSplitComponent.onUnload();
}

void LiveSplitToolkit::render()
{
    this->liveSplitComponent.render();
}
