#include <sstream>
#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include "KismetToolkit.h"

KismetToolkit::KismetToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), sequenceVariableComponent(plugin)
{

}

std::string KismetToolkit::title()
{
    return "Kismet";
}

void KismetToolkit::onLoad()
{
    this->sequenceVariableComponent.onLoad();

    this->plugin->cvarManager->registerNotifier("speedrun_kismet_list", [this](const std::vector<std::string> &commands) {
        this->onListSequenceVars();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void KismetToolkit::onUnload()
{
    this->sequenceVariableComponent.onUnload();
}

void KismetToolkit::render()
{
    ImGui::Spacing();

    ImGui::Text("Kismet Toolkit allows you to view kismet sequence variables (useful in workshop maps).");
    ImGui::Text("The following tools will only work in freeplay and workshop maps.");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->sequenceVariableComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
}

void KismetToolkit::onListSequenceVars()
{
    SequenceWrapper sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL)
    {
        this->plugin->cvarManager->log("KismetToolkit: Unable to list sequence variables. No main sequence was found.");
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
