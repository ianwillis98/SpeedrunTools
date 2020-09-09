#include "AnalysisToolkit.h"

AnalysisToolkit::AnalysisToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), carAnalysisComponent(plugin), ballAnalysisComponent(plugin)
{

}

std::string AnalysisToolkit::title()
{
    return "Analysis";
}

void AnalysisToolkit::onLoad()
{
    this->carAnalysisComponent.onLoad();
    this->ballAnalysisComponent.onLoad();
}

void AnalysisToolkit::onUnload()
{
    this->carAnalysisComponent.onUnload();
    this->ballAnalysisComponent.onUnload();
}

void AnalysisToolkit::render()
{
    ImGui::Spacing();

    ImGui::Text("Analysis Toolkit allows you to view important stats about the current game.");
    ImGui::Text("The following tools will only work in freeplay and workshop maps.");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->carAnalysisComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->ballAnalysisComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
}
