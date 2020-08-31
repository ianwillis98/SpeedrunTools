#include <sstream>
#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include "PanicsAirRaceBeachComponent.h"
#include "../../../services/MultiEventHooker.h"

PanicsAirRaceBeachComponent::PanicsAirRaceBeachComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponent(plugin)
{

}

void PanicsAirRaceBeachComponent::onLoad()
{
    CVarWrapper componentEnabled = this->plugin->cvarManager->registerCvar("speedrun_autosplitter_airracebeach", "0", "Auto splitter enabled");
    componentEnabled.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onComponentEnabledChanged();
    });

    this->plugin->cvarManager->registerNotifier("seqvar_dump", [this](std::vector<std::string> parms) {
        auto seq = this->plugin->gameWrapper->GetMainSequence();
        if (seq.memory_address == NULL)
        {
            this->plugin->cvarManager->log("No main sequence");
            return;
        }
        auto a = seq.GetAllSequenceVariables(true);
        for (auto abc : a)
        {
            std::stringstream ss;
            ss << abc.first;
            ss << " = ";
            auto sec = abc.second;
            if (sec.IsBool())
            {
                ss << (sec.GetBool() ? "true" : "false");
            }
            else if (sec.IsFloat())
            {
                ss << std::to_string(sec.GetFloat()) << "f";
            }
            else if (sec.IsInt())
            {
                ss << std::to_string(sec.GetInt());
            }
            else if (sec.IsString())
            {
                ss << "str(" << sec.GetString() << ")";
            }
            else if (sec.IsVector())
            {
                ss << "Vec(" << sec.GetVector().X << ", " << sec.GetVector().Y << ", " << sec.GetVector().Z << ");";
            }
            else
            {
                ss << "Unknown";
            }
            //ss << "\n";
            this->plugin->cvarManager->log(ss.str());
        }
    }, "", PERMISSION_ALL);

    SequenceWrapper seq = this->plugin->gameWrapper->GetMainSequence();
    if (seq.memory_address == NULL) return;
    auto a = seq.GetAllSequenceVariables(false);

    static auto find = a.find("Player1Count");

    this->plugin->cvarManager->log("Player1Count: test");

    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this, &a](const std::string &eventName) {
        if (find != a.end())
        {
            this->plugin->cvarManager->log("player 1 count " + std::to_string(find->second.GetInt()));
        }
    });
//        SequenceWrapper seq = this->plugin->gameWrapper->GetMainSequence();
//        if (seq.memory_address == NULL) return;
//        auto a = seq.GetAllSequenceVariables(false);
//
//        auto find = a.find("Player1Count");
//        if (find != a.end()) {
//            this->plugin->cvarManager->log("player 1 count " + std::to_string(find->second.GetInt()));
//        }
//        this->plugin->cvarManager->log("Player1Count: test");
}

void PanicsAirRaceBeachComponent::onUnload()
{

}

void PanicsAirRaceBeachComponent::render()
{

}

bool PanicsAirRaceBeachComponent::isComponentEnabled()
{
    return this->plugin->cvarManager->getCvar("speedrun_autosplitter_airracebeach").getBoolValue();
}

void PanicsAirRaceBeachComponent::setComponentEnabled(bool enabled)
{
    this->plugin->cvarManager->getCvar("speedrun_autosplitter_airracebeach").setValue(enabled);
}

void PanicsAirRaceBeachComponent::onComponentEnabledChanged()
{

}

