#include "SpeedJumpRings3AutoSplitterComponent.h"

SpeedJumpRings3AutoSplitterComponent::SpeedJumpRings3AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          timer(),
          level()
{

}
void SpeedJumpRings3AutoSplitterComponent::onEnable()
{
    this->timer = this->kismetModel.getStringValue("displayTimer");
    this->level = this->kismetModel.getIntValue("Level");
}

void SpeedJumpRings3AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        std::string previousTimer = this->timer;
        this->timer = this->kismetModel.getStringValue("displayTimer");

        int previousLevel = this->level;
        this->level = this->kismetModel.getIntValue("Level");

        if (this->segment == 0)
        {
            if (this->timer == "00:00" && previousTimer != "00:00")
            {
                this->start();
            }
        }
        else if (1 <= this->segment && this->segment <= 13)
        {
            if (this->level == (previousLevel + 1))
            {
                this->split();
            }
        }
        else if (this->segment == 14)
        {
            if (this->level == 1 && previousLevel == 14) this->split();
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        if (this->segment > 0)
        {
            this->reset();
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
    ss << "timer = " << this->timer << std::endl;
    ss << "level = " << this->level << std::endl;
    return ss.str();
}
