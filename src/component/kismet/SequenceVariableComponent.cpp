#include <sstream>
#include "SequenceVariableComponent.h"
#include "../../utils/ImGuiExtensions.h"
#include "../../services/MultiEventHooker.h"

SequenceVariableComponent::SequenceVariableComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), variables(), selectedRow(-1)
{

}

void SequenceVariableComponent::onLoad()
{
    // Function TAGame.GameEvent_TA.Destroyed
    // Function TAGame.GameEvent_TA.EventDestroyed
    // Function TAGame.GameEvent_TA.IsFinished
    // Function GameEvent_Soccar_TA.Active.EndRound
    // Function TAGame.GameEvent_Soccar_TA.EventMatchEnded

    MultiEventHooker::getInstance(this->plugin).hookEvent("Function GameEvent_Soccar_TA.Active.EndRound", [this](const std::string &eventName) {
        //this->variables.clear();
    });
}

void SequenceVariableComponent::onUnload()
{

}

void SequenceVariableComponent::render()
{
    ImGui::PushID(this);

    ImGui::Text("Kismet Sequence Variables:");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);

    if (ImGui::Button("Refresh Table"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->loadSequenceVariables();
        });
    }

    ImGui::Columns(3, "Sequence Vars");
    ImGui::Separator();
    ImGui::Text("Name");
    ImGui::NextColumn();
    ImGui::Text("Value");
    ImGui::NextColumn();
    ImGui::Text("Type");
    ImGui::NextColumn();
    ImGui::Separator();

    for (int i = 0; i < this->variables.size(); i++)
    {
        auto var = this->variables.at(i);

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

    ImGui::PopID();
}

void SequenceVariableComponent::loadSequenceVariables()
{
    SequenceWrapper sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    this->variables.clear();
    for (const auto &var : sequence.GetAllSequenceVariables(true))
    {
        this->variables.emplace_back(var.second);
    }
}
