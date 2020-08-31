#include "LiveSplitToolkit.h"

LiveSplitToolkit::LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), liveSplitComponent(plugin), panicsAirRaceBeachComponent(plugin)
{

}

std::string LiveSplitToolkit::title()
{
    return "LiveSplit Toolkit";
}

void LiveSplitToolkit::onLoad()
{
    this->liveSplitComponent.onLoad();
    this->panicsAirRaceBeachComponent.onLoad();
}

void LiveSplitToolkit::onUnload()
{
    this->liveSplitComponent.onUnload();
    this->panicsAirRaceBeachComponent.onUnload();
}

void LiveSplitToolkit::render()
{
    ImGui::Spacing();

    this->liveSplitComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->panicsAirRaceBeachComponent.render();

    ImGui::Spacing();
}
