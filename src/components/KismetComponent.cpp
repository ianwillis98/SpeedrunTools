#include "KismetComponent.h"

KismetComponent::KismetComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), kismetVars(), selectedRow(-1)
{

}

std::string KismetComponent::title()
{
    return "Kismet Editor";
}

void KismetComponent::onLoad()
{
    this->plugin->cvarManager->registerNotifier("speedrun_kismet_list", [this](const std::vector<std::string> &commands) {
        this->listSequenceVars();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void KismetComponent::render()
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

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
    ImGuiExtensions::PushDisabledStyleIf(!isInFreeplay);
    ImGui::Spacing();
    if (ImGui::Button("Refresh Table"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->loadSequenceVariables();
        });
    }
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

void KismetComponent::listSequenceVars()
{
    SequenceWrapper sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL)
    {
        this->plugin->cvarManager->log("Kismet Viewer: Unable to list sequence variables. No main sequence was found.");
        return;
    }

    std::map<std::string, SequenceVariableWrapper> variables = sequence.GetAllSequenceVariables(true);
    for (const auto &pair : variables)
    {
        std::string name = pair.first;
        SequenceVariableWrapper var = pair.second;

        std::stringstream ss;
        ss << name;
        ss << " = ";
        if (var.IsBool())
        {
            ss << (var.GetBool() ? "true" : "false");
        }
        else if (var.IsInt())
        {
            ss << std::to_string(var.GetInt());
        }
        else if (var.IsFloat())
        {
            ss << std::to_string(var.GetFloat()) << "f";
        }
        else if (var.IsVector())
        {
            ss << "Vec(" << var.GetVector().X << ", " << var.GetVector().Y << ", " << var.GetVector().Z << ");";
        }
        else if (var.IsString())
        {
            ss << "\"" << var.GetString() << "\"";
        }
        else
        {
            ss << "Unknown";
        }
        this->plugin->cvarManager->log(ss.str());
    }
}

void KismetComponent::loadSequenceVariables()
{
    this->kismetVars.clear();

    SequenceWrapper sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    for (const auto &var : sequence.GetAllSequenceVariables(true))
    {
        this->kismetVars.emplace_back(var.second);
    }
}
