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

    this->carAnalysisComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->ballAnalysisComponent.render();

    ImGui::Spacing();
}
