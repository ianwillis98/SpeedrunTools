#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin),
          liveSplitRemoteComponent(plugin),
          autoSplitterComponent(plugin)
{

}
std::string LiveSplitToolkit::title()
{
    return "LiveSplit Controller";
}

void LiveSplitToolkit::onLoad()
{
    this->liveSplitRemoteComponent.onLoad();
    this->autoSplitterComponent.onLoad();
}

void LiveSplitToolkit::render()
{
    ImGuiExtensions::BigSpacing();
    this->liveSplitRemoteComponent.render();
    ImGuiExtensions::BigSeparator();
    this->autoSplitterComponent.render();
}

void LiveSplitToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->liveSplitRemoteComponent.onEvent(eventName, post, params);
    this->autoSplitterComponent.onEvent(eventName, post, params);
}
