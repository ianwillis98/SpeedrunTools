#include "Dribble2OverhaulAutoSplitterComponent.h"

Dribble2OverhaulAutoSplitterComponent::Dribble2OverhaulAutoSplitterComponent(NetcodePlugin* plugin)
    : AutoSplitterComponent(plugin),
    checkpoint(),
    timing()
{

}

void Dribble2OverhaulAutoSplitterComponent::onEnable()
{
    this->checkpoint = this->kismetModel.getIntValue("Level");
    this->timing = this->kismetModel.getBoolValue("Timing");
}

void Dribble2OverhaulAutoSplitterComponent::update(const std::string& eventName, bool post, void* params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        int previousCheckpoint = this->checkpoint;
        this->checkpoint = this->kismetModel.getIntValue("Level");

        bool previousTiming = this->timing;
        this->timing = this->kismetModel.getBoolValue("Timing");

        if (this->segment == 0)
        {
            if(this->timing && !previousTiming)
                this->start();
        }
        else if (this->segment > 0 && this->segment <= 29)
        {
            if (this->checkpoint == (previousCheckpoint + 1) && this->checkpoint == (this->segment + 1))
                this->split();
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset();
    }
    if (eventName == "Function TAGame.Ball_TA.Explode" && post)
    {
        if (this->segment == 30)
            this->split();
    }
}

std::string Dribble2OverhaulAutoSplitterComponent::getStartDescription()
{
    return "The timer will start when you hit the timer box.";
}

std::string Dribble2OverhaulAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split when the ball hits each of the goals and ends on the final goal. (30 splits in total).";
}

std::string Dribble2OverhaulAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset after leaving the match.";
}

std::string Dribble2OverhaulAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Dribble Challenge 2 Auto Splitter (Debug)" << std::endl;
    ss << "checkpoint = " << this->checkpoint << std::endl;
    ss << "timing = " << this->timing << std::endl;
    return ss.str();
}
