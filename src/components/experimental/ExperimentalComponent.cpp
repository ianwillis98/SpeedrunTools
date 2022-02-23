#include "ExperimentalComponent.h"

ExperimentalComponent::ExperimentalComponent(NetcodePlugin *plugin)
        : PluginComponentBase(plugin), vars()
{

}

void ExperimentalComponent::render()
{
    if (ImGui::Button("Assign"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->assign();
        });
    }
    static bool show = false;
    ImGui::Checkbox("Show", &show);
    if (show)
    {
        for (auto &var : this->vars)
        {
            ImGui::Text("%s", var.getName().c_str());
        }
    }
}

void ExperimentalComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{

}

void ExperimentalComponent::onEvent(const std::string &eventName, bool post, void *params)
{

}
void ExperimentalComponent::assign()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();

    if (sequence.memory_address != NULL)
    {
        auto s = sequence.GetAllSequenceVariables(false);
        for (auto &v : s)
        {
            if (v.first == "Level")
            {
                this->vars.emplace_back(v.second);
            }
        }
    }
}


