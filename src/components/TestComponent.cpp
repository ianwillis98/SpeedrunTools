#include "TestComponent.h"

TestComponent::TestComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponent(plugin), liveSplitClient(LiveSplitClient::getInstance()), running(false), previousLevel(0), previousTiming(false)
{

}

std::string TestComponent::title()
{
    return "Test Features (remove before release)";
}

void TestComponent::onLoad()
{
    this->plugin->cvarManager->registerNotifier("speedrun_test", [this](const std::vector<std::string> &commands) {
        this->changeLevel();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void TestComponent::render()
{
    if (this->liveSplitClient.getConnectionState() != ConnectionState::Connected)
    {
        ImGui::Text("Waiting for LiveSplit Server connection...");
    }
    else
    {
        ImGui::Checkbox("Auto Splitter Enabled", &this->running);
    }
}

void TestComponent::onEvent(std::string eventName, bool post, void *params)
{
    //this->plugin->cvarManager->log(this->plugin->gameWrapper->GetCurrentMap());

    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (!this->running) return;
        if (this->plugin->gameWrapper->GetCurrentMap() != "dribblechallenge2overhaul") return;
        if (this->liveSplitClient.getConnectionState() != ConnectionState::Connected) return;

        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto vars = sequence.GetAllSequenceVariables(false);
        auto levelVar = vars.find("Level");
        auto timedVar = vars.find("Timing");

        if (levelVar != vars.end() && timedVar != vars.end())
        {
            int level = levelVar->second.GetInt();
            bool timing = timedVar->second.GetBool();

            if (timing && !previousTiming && level == 1)
            {
                // start the timer
                this->liveSplitClient.start([](int errorCode, const std::string &errorMessage) {});
            }
            if (timing && level > 1 && level != previousLevel)
            {
                // next level
                this->liveSplitClient.split([this](int errorCode, const std::string &errorMessage) {});
            }
            if (timing && level == 1 && previousLevel == 30)
            {
                // finished
                this->liveSplitClient.split([this](int errorCode, const std::string &errorMessage) {});
            }

            this->previousLevel = level;
            this->previousTiming = timing;
        }
    }
}

void TestComponent::changeLevel()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto vars = sequence.GetAllSequenceVariables(false);

    auto levelVar = vars.find("Level");
    if (levelVar == vars.end()) return;

    auto timingVar = vars.find("Timing");
    if (timingVar == vars.end()) return;


    levelVar->second.SetInt(30);
    timingVar->second.SetBool(true);
}
