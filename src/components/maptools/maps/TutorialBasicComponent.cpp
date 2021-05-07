#include "TutorialBasicComponent.h"

TutorialBasicComponent::TutorialBasicComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          tutorialBasicAutoSplitterComponent(plugin)
{

}

void TutorialBasicComponent::render()
{
    ImGui::Text("Tutorial Basic Map Tools");
    ImGuiExtensions::BigSeparator();
    ImGui::Text("Tutorial Basic Auto Splitter");
    ImGui::Spacing();
    tutorialBasicAutoSplitterComponent.render();
}

void TutorialBasicComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    tutorialBasicAutoSplitterComponent.onEvent(eventName, post, params);
}
