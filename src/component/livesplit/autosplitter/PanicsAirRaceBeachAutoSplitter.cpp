#include "PanicsAirRaceBeachAutoSplitter.h"
#include "../../../services/MultiEventHooker.h"

PanicsAirRaceBeachAutoSplitter::PanicsAirRaceBeachAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin, LiveSplitClient &liveSplitClient)
        : PluginComponent(plugin), liveSplitClient(liveSplitClient), isAutoSplitterRunning(false), previousCount(0), previousCpCount(0)
{

}

void PanicsAirRaceBeachAutoSplitter::onLoad()
{

    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &eventName) {
        this->onPhysicsTick();
    });
}

void PanicsAirRaceBeachAutoSplitter::onUnload()
{

}

void PanicsAirRaceBeachAutoSplitter::render()
{
    if (this->liveSplitClient.getConnectionState() != ConnectionState::Connected)
    {
        ImGui::Text("Waiting for LiveSplit Server connection...");
    }
    else
    {
        if (ImGui::Button("Start the Auto Splitter"))
        {
            this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                this->startAutoSplitter();
            });
        }
    }
}

void PanicsAirRaceBeachAutoSplitter::onPhysicsTick()
{
    if (!this->isAutoSplitterRunning) return;
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto vars = sequence.GetAllSequenceVariables(false);

    auto countVar = vars.find("Player1Count");
    if (countVar != vars.end())
    {
        int count = countVar->second.GetInt();
        if (count == 0 && count != this->previousCount)
        {
            this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
                this->plugin->cvarManager->log("reset " + std::to_string(errorCode));
            });
        }
        if (count == 1 && count != this->previousCount)
        {
            this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
                this->plugin->cvarManager->log("start " + std::to_string(errorCode));
            });
        }
        if (count > 0 && count % 5 == 0 && count != this->previousCount)
        {
            this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
                this->plugin->cvarManager->log("split " + std::to_string(errorCode));
            });
        }

        this->previousCount = count;
    }

    auto cpCountVar = vars.find("Player1CPCount");
    if (cpCountVar != vars.end())
    {
        int cpCount = cpCountVar->second.GetInt();
        if (cpCount == 12 && cpCount != this->previousCpCount)
        {
            this->plugin->cvarManager->log("IT CHANGED ====== " + std::to_string(cpCount));
            this->liveSplitClient.startOrSplit([this](const int &errorCode, const std::string &errorMessage) {
                this->plugin->cvarManager->log("start or split ending" + std::to_string(errorCode));
            });
        }

        this->previousCpCount = cpCount;
    }
}

void PanicsAirRaceBeachAutoSplitter::startAutoSplitter()
{
    if (this->isAutoSplitterRunning) return;

    this->isAutoSplitterRunning = true;
}
