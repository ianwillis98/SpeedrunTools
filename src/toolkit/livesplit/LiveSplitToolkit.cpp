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
    ImGui::Spacing();

    ImGui::Text("NOTE: You must have both LiveSplit AND LiveSplit Server installed for this to work");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->liveSplitComponent.render();
}
