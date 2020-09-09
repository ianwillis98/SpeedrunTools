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
        ImGui::Text("Auto splitter will split after crossing the 6th ring and after crossing each check point.");
        ImGui::Checkbox("Auto Splitter Enabled", &this->isAutoSplitterRunning);
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
                if (errorCode == 0)
                {
                    this->plugin->gameWrapper->Execute([](GameWrapper *gw) {
                        gw->LogToChatbox("AutoSplitter: reset", "SPEEDRUNTOOLS");
                    });
                }
            });
        }
        if (count == 1 && count != this->previousCount)
        {
            this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
                if (errorCode == 0)
                {
                    this->plugin->gameWrapper->Execute([](GameWrapper *gw) {
                        gw->LogToChatbox("AutoSplitter: start", "SPEEDRUNTOOLS");
                    });
                }
            });
        }
        if (count == 6 && count != this->previousCount)
        {
            this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
                if (errorCode == 0)
                {
                    this->plugin->gameWrapper->Execute([](GameWrapper *gw) {
                        gw->LogToChatbox("AutoSplitter: split", "SPEEDRUNTOOLS");
                    });
                }
            });
        }

        this->previousCount = count;
    }

    auto cpCountVar = vars.find("Player1CPCount");
    if (cpCountVar != vars.end())
    {
        int cpCount = cpCountVar->second.GetInt();
        if (cpCount > 0 && cpCount != this->previousCpCount)
        {
            this->liveSplitClient.split([this, cpCount](const int &errorCode, const std::string &errorMessage) {
                if (errorCode == 0)
                {
                    this->plugin->gameWrapper->Execute([](GameWrapper *gw) {
                        gw->LogToChatbox("AutoSplitter: split", "SPEEDRUNTOOLS");
                    });
                }
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

void PanicsAirRaceBeachAutoSplitter::stopAutoSplitter()
{
    if (!this->isAutoSplitterRunning) return;

    this->isAutoSplitterRunning = false;
}
