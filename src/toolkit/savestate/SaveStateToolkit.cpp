#include "SaveStateToolkit.h"

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), saveStateComponent(plugin)
{

}

std::string SaveStateToolkit::title()
{
    return "Save State Toolkit";
}

void SaveStateToolkit::onLoad()
{
    this->saveStateComponent.onLoad();
}

void SaveStateToolkit::onUnload()
{
    this->saveStateComponent.onUnload();
}

void SaveStateToolkit::render()
{
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->saveStateComponent.render();

    ImGui::Spacing();
}
