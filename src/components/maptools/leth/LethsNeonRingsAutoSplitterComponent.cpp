#include "LethsNeonRingsAutoSplitterComponent.h"

LethsNeonRingsAutoSplitterComponent::LethsNeonRingsAutoSplitterComponent(NetcodePlugin *plugin)
        : AutoSplitterComponent(plugin),
          level(),
          timing()
{
}

void LethsNeonRingsAutoSplitterComponent::onEnable()
{
    this->timing = this->kismetModel.getBoolValue("Timing");
    this->level = this->kismetModel.getIntValue("Level");
}

void LethsNeonRingsAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        bool previousTiming = this->timing;
        this->timing = this->kismetModel.getBoolValue("Timing");

        int previousLevel = this->level;
        this->level = this->kismetModel.getIntValue("Level");

        if (this->segment == 0)
        {
            if (this->timing && !previousTiming)
            {
                this->start();
            }
        }
        else if (1 <= this->segment && this->segment <= 19)
        {
            if (this->level == (previousLevel + 1) && this->level == (this->segment + 1))
            {
                this->split();
            }
        }
        else if (this->segment == 20)
        {
            if (this->level == 1 && previousLevel == 20)
            {
                this->split();
            }
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset();
    }
}

std::string LethsNeonRingsAutoSplitterComponent::getStartDescription()
{
    return "The timer will start when map timer starts.";
}

std::string LethsNeonRingsAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after completing each level (20 splits in total).";
}

std::string LethsNeonRingsAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset after leaving the map.";
}

std::string LethsNeonRingsAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Leth's Neon Rings Auto Splitter (Debug)" << std::endl;
    ss << "timing = " << this->timing << std::endl;
    ss << "level = " << this->level << std::endl;
    return ss.str();
}
