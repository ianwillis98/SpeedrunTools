#include "KismetEditorComponent.h"

KismetEditorComponent::KismetEditorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          kismetVars(),
          shouldAutoReloadKismetVars(false),
          mutex()
{

}

void KismetEditorComponent::onLoad()
{
    this->loadKismetVars();
}

void KismetEditorComponent::render()
{
    ImGui::Text("Kismet Sequence Variable Editor");
    ImGui::Spacing();

    ImGuiExtensions::PushDisabledStyleIf(this->shouldAutoReloadKismetVars);
    if (ImGui::Button("Refresh"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->loadKismetVars();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(this->shouldAutoReloadKismetVars);
    ImGui::SameLine();
    ImGui::Checkbox("Auto Refresh", &this->shouldAutoReloadKismetVars);

    ImGui::Spacing();

    ImGui::Columns(3, "Kismet Variables");
    ImGui::Separator();
    ImGui::Text("Name");
    ImGui::NextColumn();
    ImGui::Text("Value");
    ImGui::NextColumn();
    ImGui::Text("Type");
    ImGui::NextColumn();
    ImGui::Separator();

    mutex.lock();
    for (auto &var : this->kismetVars)
    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", var.getName().c_str());
        ImGui::NextColumn();

        if (var.render())
        {
            this->plugin->gameWrapper->Execute([var](GameWrapper *gw) {
                var.updateMainSequenceValue();
            });
        }
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", var.getTypeAsString().c_str());
        ImGui::NextColumn();
    }
    mutex.unlock();

    ImGui::Columns(1);
    ImGui::Separator();
}

void KismetEditorComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        if (this->shouldAutoReloadKismetVars) this->loadKismetVars();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        mutex.lock();
        this->kismetVars.clear();
        mutex.unlock();
    }
}

void KismetEditorComponent::loadKismetVars()
{
    mutex.lock();

    this->kismetVars.clear();

    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address != NULL)
    {
        auto vars = sequence.GetAllSequenceVariables(false);

        for (auto &var : vars)
        {
            this->kismetVars.emplace_back(this->plugin, var.second);
        }
    }

    mutex.unlock();
}
