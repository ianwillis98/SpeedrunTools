#include "SpeedJumpRings3AutoSplitterComponent.h"

SpeedJumpRings3AutoSplitterComponent::SpeedJumpRings3AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          hasUpdatedOnce(),
          hasUpdatedTwice(),
          currentDisplayTimer(),
          previousDisplayTimer(),
          currentLevel(),
          previousLevel(),
          segment(0)
{

}
void SpeedJumpRings3AutoSplitterComponent::onEnable()
{
    this->hasUpdatedOnce = false;
    this->hasUpdatedTwice = false;
}

void SpeedJumpRings3AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto displayTimer = allVars.find("displaytimer");
        if (displayTimer == allVars.end()) return;

        this->previousDisplayTimer = this->currentDisplayTimer;
        this->currentDisplayTimer = displayTimer->second.GetString();

        auto level = allVars.find("Level");
        if (level == allVars.end()) return;

        this->previousLevel = this->currentLevel;
        this->currentLevel = level->second.GetInt();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->segment == 0)
            {
                if (this->currentDisplayTimer == "00:00" && this->previousDisplayTimer != "00:00")
                {
                    this->segment++;
                    this->startTimer();
                }
            }
            else if (1 <= this->segment && this->segment <= 13)
            {
                if (this->currentLevel == (this->previousLevel + 1))
                {
                    this->segment++;
                    this->splitTimer();
                }
            }
            else if (this->segment == 14)
            {
                if (this->currentLevel == 1 && this->previousLevel == 14)
                {
                    this->segment++;
                    this->splitTimer();
                }
            }
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->segment == 14)
        {
            this->segment++;
            this->splitTimer();
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;
        if (this->segment > 0)
        {
            this->segment = 0;
            this->resetTimer();
        }
    }
}

std::string SpeedJumpRings3AutoSplitterComponent::getStartDescription()
{
    return AutoSplitterComponent::getStartDescription();
}

std::string SpeedJumpRings3AutoSplitterComponent::getSplitDescription()
{
    return AutoSplitterComponent::getSplitDescription();
}

std::string SpeedJumpRings3AutoSplitterComponent::getResetDescription()
{
    return AutoSplitterComponent::getResetDescription();
}

std::string SpeedJumpRings3AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 3 Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentDisplayTimer = " << this->currentDisplayTimer << std::endl;
    ss << "previousDisplayTimer = " << this->previousDisplayTimer << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    ss << "segment = " << this->segment << std::endl;
    return ss.str();
}
