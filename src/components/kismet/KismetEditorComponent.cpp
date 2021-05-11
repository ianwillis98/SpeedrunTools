#include "KismetEditorComponent.h"

const std::string KismetEditorComponent::ListAllCVarsNotifier = "speedrun_kismet_list";

KismetEditorComponent::KismetEditorComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          kismetVars(),
          shouldAutoReloadKismetVars(false),
          mutex()
{
    this->updateKismetVars();
    this->plugin->cvarManager->registerNotifier(ListAllCVarsNotifier, [this](const std::vector<std::string> &commands) {
        this->listCVarsToConsole();
    }, "", PERMISSION_ALL);
}

void KismetEditorComponent::render()
{
    ImGuiExtensions::PushDisabledStyleIf(this->shouldAutoReloadKismetVars);
    if (ImGui::Button("Refresh"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->updateKismetVars();
        });
    }
    ImGuiExtensions::PopDisabledStyleIf(this->shouldAutoReloadKismetVars);
    ImGui::SameLine();
    ImGui::Checkbox("Auto Refresh", &this->shouldAutoReloadKismetVars);

    ImGui::Spacing();

    mutex.lock();
    if (this->kismetVars.empty())
    {
        ImGui::Text("No kismet variables were found. Try refreshing or switching maps.");
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

        ImGui::Columns(1);
        ImGui::Separator();
    }
    mutex.unlock();
}

void KismetEditorComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        if (this->shouldAutoReloadKismetVars)
        {
            this->updateKismetVars();
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.InitGame" && post)
    {
        this->plugin->gameWrapper->SetTimeout([this](GameWrapper *gw) {
            this->updateKismetVars();
        }, 1.0f);
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        mutex.lock();
        this->kismetVars.clear();
        mutex.unlock();
    }
}

std::vector<KismetSequenceVariable> KismetEditorComponent::loadKismetVars()
{
    std::vector<KismetSequenceVariable> loaded;

    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address != NULL)
    {
        auto vars = sequence.GetAllSequenceVariables(false);

        for (auto &var : vars)
        {
            loaded.emplace_back(this->plugin, var.second);
        }
    }

    return loaded;
}

void KismetEditorComponent::updateKismetVars()
{
    std::vector<KismetSequenceVariable> loaded = this->loadKismetVars();
    mutex.lock();
    this->kismetVars = loaded;
    mutex.unlock();
}

void KismetEditorComponent::listCVarsToConsole()
{
    std::vector<KismetSequenceVariable> kismetVars = this->loadKismetVars();
    this->plugin->cvarManager->log("Listing all kismet variables:");
    for (auto &var : kismetVars)
    {
        this->plugin->cvarManager->log(var.getName() + ": " + var.getValueAsString());
    }
    this->plugin->cvarManager->log("Listing complete.");
}
