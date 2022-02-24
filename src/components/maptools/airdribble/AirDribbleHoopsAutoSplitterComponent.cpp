#include "AirDribbleHoopsAutoSplitterComponent.h"

AirDribbleHoopsAutoSplitterComponent::AirDribbleHoopsAutoSplitterComponent(NetcodePlugin *plugin)
        : AutoSplitterComponent(plugin),
          timer(),
          level()
{

}

void AirDribbleHoopsAutoSplitterComponent::onEnable()
{
    this->timer = this->kismetModel.getBoolValue("Timer");
    this->level = this->kismetModel.getIntValue("Level");
}

void AirDribbleHoopsAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        bool previousTimer = this->timer;
        this->timer = this->kismetModel.getBoolValue("Timer");

        int previousLevel = this->level;
        this->level = this->kismetModel.getIntValue("Level");

        if (this->segment == 0)
        {
            if (this->timer && !previousTimer)
            {
                this->start();
            }
        }
        if (1 <= this->segment && this->segment <= 20)
        {
            if (this->level == (previousLevel + 1) && this->level == (this->segment + 1)) {
                this->split();
            }
        }
        if (this->segment == 21)
        {
            if (this->level == 1 && previousLevel == 21)
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

std::string AirDribbleHoopsAutoSplitterComponent::getStartDescription()
{
    return "The timer will start at the selection of \"Speedrun Mode\".";
}

std::string AirDribbleHoopsAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after completing each level (21 splits in total).";
}

std::string AirDribbleHoopsAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset after leaving the match.";
}

std::string AirDribbleHoopsAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Air Dribble Hoops Auto Splitter (Debug)" << std::endl;
    ss << "timer = " << this->timer << std::endl;
    ss << "level = " << this->level << std::endl;
    return ss.str();
}
