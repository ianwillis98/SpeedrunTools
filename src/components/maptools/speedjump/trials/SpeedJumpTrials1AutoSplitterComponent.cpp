#include "SpeedJumpTrials1AutoSplitterComponent.h"

SpeedJumpTrials1AutoSplitterComponent::SpeedJumpTrials1AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          level(),
          resetMap()
{

}

void SpeedJumpTrials1AutoSplitterComponent::onEnable()
{
    this->level = this->kismetModel.getIntValue("Level");
    this->resetMap = this->kismetModel.getBoolValue("Reset");
}

void SpeedJumpTrials1AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        int previousLevel = this->level;
        this->level = this->kismetModel.getIntValue("Level");

        this->resetMap = this->kismetModel.getBoolValue("Reset");

        if (this->segment == 0)
        {
            CarWrapper carWrapper = this->plugin->gameWrapper->GetLocalCar();
            if (!carWrapper.IsNull())
            {
                if (carWrapper.GetLocation().X >= 1408.0f) this->start();
            }
        }
        if (this->segment == 1)
        {
            if (this->level == 2 && previousLevel == 0)
            {
                this->split();
            }
        }
        else if (2 <= this->segment && this->segment <= 9)
        {
            // TODO CHECK SEG
            if (this->level == (previousLevel + 1))
            {
                this->split();
            }
        }
        else if (this->segment == 10)
        {
            // TODO ENSURE NOT RESET
            if (this->level == 0 && previousLevel == 10)
            {
                this->split();
            }
        }

    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining" && post)
    {
        if (this->level == 1) {
            this->reset();
        }
        if (this->resetMap)
        {
            this->reset();
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset();
    }
}

std::string SpeedJumpTrials1AutoSplitterComponent::getStartDescription()
{
    return "The timer will start when the in game timer starts.";
}

std::string SpeedJumpTrials1AutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after finishing each level (10 splits in total).";
}

std::string SpeedJumpTrials1AutoSplitterComponent::getResetDescription()
{
    return "The timer will reset when the player resets the map or leaves the match.";
}

std::string SpeedJumpTrials1AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Trials 1 Auto Splitter (Debug)" << std::endl;
    ss << "level = " << this->level << std::endl;
    ss << "resetMap = " << this->resetMap << std::endl;
    return ss.str();
}
