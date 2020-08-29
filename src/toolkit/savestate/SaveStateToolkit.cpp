#include "SaveStateToolkit.h"

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), rewindStateComponent(plugin), saveStateComponent(plugin)
{

}

std::string SaveStateToolkit::title()
{
    return "Save State Toolkit";
}

void SaveStateToolkit::onLoad()
{
    this->rewindStateComponent.onLoad();
    this->saveStateComponent.onLoad();
}

void SaveStateToolkit::onUnload()
{
    this->rewindStateComponent.onUnload();
    this->saveStateComponent.onUnload();
}

void SaveStateToolkit::render()
{
    ImGui::Spacing();

    this->rewindStateComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->saveStateComponent.render();

    ImGui::Spacing();
}
