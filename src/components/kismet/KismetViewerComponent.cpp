#include "KismetViewerComponent.h"

KismetViewerComponent::KismetViewerComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          kismetVars(),
          selectedRow(-1),
          autoRefresh(false)
{

}

void KismetViewerComponent::onLoad()
{
    this->autoRefreshFunc();
}

void KismetViewerComponent::render()
{
    ImGui::Spacing();
    ImGui::Text("View kismet sequence variables (useful in workshop maps).");
    ImGui::Text("Editing kismet vars is not yet supported by BakkesMod (likely coming soon).");
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::Text("Kismet Sequence Variables:");

    bool isInFreeplay = true || this->plugin->gameWrapper->IsInFreeplay();
    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    ImGui::Spacing();
    if (ImGui::Button("Refresh Table"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->loadSequenceVariables();
        });
    }
    ImGui::Spacing();

    ImGui::Checkbox("Auto Refresh", &this->autoRefresh);
    ImGui::Spacing();

    ImGui::Columns(3, "Sequence Vars");
    ImGui::Separator();
    ImGui::Text("Name");
    ImGui::NextColumn();
    ImGui::Text("Value");
    ImGui::NextColumn();
    ImGui::Text("Type");
    ImGui::NextColumn();
    ImGui::Separator();
    for (int i = 0; i < this->kismetVars.size(); i++)
    {
        auto var = this->kismetVars.at(i);

        if (ImGui::Selectable(var.getName().c_str(), this->selectedRow == i, ImGuiSelectableFlags_SpanAllColumns))
            this->selectedRow = i;
        ImGui::NextColumn();

        ImGui::Text("%s", var.getValueAsString().c_str());
        ImGui::NextColumn();
        ImGui::Text("%s", var.getTypeAsString().c_str());
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::Separator();
    ImGuiExtensions::PopDisabledStyleIf(!isInFreeplay);
}

void KismetViewerComponent::onEvent(const std::string &eventName, bool post, void *params)
{

}

void KismetViewerComponent::loadSequenceVariables()
{
    this->kismetVars.clear();

    SequenceWrapper sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    for (const auto &var : sequence.GetAllSequenceVariables(true))
    {
        this->kismetVars.emplace_back(this->plugin, var.second);
    }
}
void KismetViewerComponent::autoRefreshFunc()
{
    this->plugin->gameWrapper->SetTimeout([this](GameWrapper *gw) {
        if (this->autoRefresh)
        {
            this->plugin->cvarManager->log("RELOADING");
            this->loadSequenceVariables();
        }
        this->autoRefreshFunc();
    }, 1.0f);
}
