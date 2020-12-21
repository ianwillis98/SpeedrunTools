#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin),
          liveSplitRemoteComponent(this->plugin),
          autoSplitterComponent(this->plugin)
{

}
std::string LiveSplitToolkit::title()
{
    return "Auto splitter testing";
}

void LiveSplitToolkit::onLoad()
{
    this->liveSplitRemoteComponent.onLoad();
    this->autoSplitterComponent.onLoad();
}

void LiveSplitToolkit::render()
{
    this->liveSplitRemoteComponent.render();
    ImGuiExtensions::BigSeparator();
    this->autoSplitterComponent.render();
    ImGuiExtensions::BigSpacing();
}

void LiveSplitToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->liveSplitRemoteComponent.onEvent(eventName, post, params);
    this->autoSplitterComponent.onEvent(eventName, post, params);
}
