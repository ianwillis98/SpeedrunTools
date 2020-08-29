#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), liveSplitComponent(plugin)
{

}

std::string LiveSplitToolkit::title()
{
    return "LiveSplit Toolkit";
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
    ImGui::Spacing();

    this->liveSplitComponent.render();

    ImGui::Spacing();
}
