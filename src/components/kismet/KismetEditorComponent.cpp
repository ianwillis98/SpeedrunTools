#include "KismetEditorComponent.h"

const std::string KismetEditorComponent::ListAllCVarsNotifier = "speedrun_kismet_list";

KismetEditorComponent::KismetEditorComponent(NetcodePlugin *plugin)
        : PluginComponentBase(plugin),
          kismetModel(KismetModel::getInstance(plugin))
{
    this->plugin->cvarManager->registerNotifier(ListAllCVarsNotifier, [this](const std::vector<std::string> &commands) {
        this->listCVarsToConsole();
    }, "", PERMISSION_ALL);
}

void KismetEditorComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->kismetModel.onEvent(eventName, post, params);
}

void KismetEditorComponent::render()
{
    std::vector<KismetVar> kismetVars = this->kismetModel.getKismetVars();

    if (kismetVars.empty())
    {
        ImGui::Text("No kismet variables were found for the current map.");
    }
    else
    {
        ImGui::Columns(3, "Kismet Variables");
        ImGui::Separator();

        ImGui::Text("Name");
        ImGui::NextColumn();

        ImGui::Text("Value");
        ImGui::NextColumn();

        ImGui::Text("Type");
        ImGui::NextColumn();

        ImGui::Separator();

        for (auto &kismetVar : kismetVars)
        {
            ImGui::AlignTextToFramePadding();
            ImGui::Text("%s", kismetVar.getName().c_str());
            ImGui::NextColumn();

            if (kismetVar.render())
            {
                this->plugin->gameWrapper->Execute([this, kismetVar](GameWrapper *gw) {
                    this->kismetModel.updateSequence(kismetVar);
                });
            }
            ImGui::NextColumn();

            ImGui::AlignTextToFramePadding();
            ImGui::Text("%s", kismetVar.getTypeAsString().c_str());
            ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
    }
}

void KismetEditorComponent::listCVarsToConsole()
{
    this->plugin->cvarManager->log("Listing all kismet variables:");
    for (auto &var : this->kismetModel.getKismetVars())
    {
        this->plugin->cvarManager->log(var.getName() + ": " + var.getValueAsString());
    }
    this->plugin->cvarManager->log("All kismet variables have been listed.");
}
