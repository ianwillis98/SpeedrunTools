#include "SpeedJumpRings2AutoSplitterComponent.h"

SpeedJumpRings2AutoSplitterComponent::SpeedJumpRings2AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentLevel(),
          previousLevel(),
          currentDisplayTimer(),
          previousDisplayTimer()
{

}

void SpeedJumpRings2AutoSplitterComponent::onEnable()
{
    this->hasUpdatedOnce = false;
    this->hasUpdatedTwice = false;
    this->resetDisplayTimer();
}

void SpeedJumpRings2AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
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

        auto displayTimer = allVars.find("displaytimer");
        if (displayTimer == allVars.end()) return;

        this->previousDisplayTimer = this->currentDisplayTimer;
        this->currentDisplayTimer = displayTimer->second.GetString();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (!this->currentDisplayTimer.empty() && this->previousDisplayTimer.empty()) this->startTimer();
            if (this->currentDisplayTimer.empty() && !this->previousDisplayTimer.empty()) this->resetTimer();
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        this->splitTimer();
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
    {
        this->resetDisplayTimer();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;
    }
}

std::string SpeedJumpRings2AutoSplitterComponent::getStartDescription()
{
    return AutoSplitterComponent::getStartDescription();
}

std::string SpeedJumpRings2AutoSplitterComponent::getSplitDescription()
{
    return AutoSplitterComponent::getSplitDescription();
}

std::string SpeedJumpRings2AutoSplitterComponent::getResetDescription()
{
    return AutoSplitterComponent::getResetDescription();
}

std::string SpeedJumpRings2AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 2 Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    return ss.str();
}

void SpeedJumpRings2AutoSplitterComponent::resetDisplayTimer()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto allVars = sequence.GetAllSequenceVariables(false);

    auto displayTimer = allVars.find("displaytimer");
    if (displayTimer == allVars.end()) return;

    displayTimer->second.SetString("");
}
