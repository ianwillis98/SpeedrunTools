#include "LethsNeonRingsAutoSplitterComponent.h"

LethsNeonRingsAutoSplitterComponent::LethsNeonRingsAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentLevel(0),
          previousLevel(0),
          currentTiming(false),
          previousTiming(false)
{
    this->supportsAutoReset = false;
}


void LethsNeonRingsAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto level = allVars.find("Level");
        if (level == allVars.end()) return;

        this->previousLevel = this->currentLevel;
        this->currentLevel = level->second.GetInt();

        auto timing = allVars.find("Timing");
        if (timing == allVars.end()) return;

        this->previousTiming = this->currentTiming;
        this->currentTiming = timing->second.GetBool();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->currentTiming && !this->previousTiming)
            {
                this->startTimer();
            }
            if (this->currentLevel != this->previousLevel)
            {
                this->splitTimer();
            }
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;
    }
}

std::string LethsNeonRingsAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    ss << "currentTiming = " << this->currentTiming << std::endl;
    ss << "previousTiming = " << this->previousTiming << std::endl;
    return ss.str();
}
