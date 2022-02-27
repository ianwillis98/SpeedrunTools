#include "PanicsAirRaceBeachAutoSplitterComponent.h"

PanicsAirRaceBeachAutoSplitterComponent::PanicsAirRaceBeachAutoSplitterComponent(NetcodePlugin *plugin)
        : AutoSplitterComponent(plugin),
          rings(),
          checkpoint()
{

}

void PanicsAirRaceBeachAutoSplitterComponent::onEnable()
{
    this->rings = this->kismetModel.getIntValue("Player1Count");
    this->checkpoint = this->kismetModel.getIntValue("Player1CPCount");
}

void PanicsAirRaceBeachAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        int previousRings = this->rings;
        this->rings = this->kismetModel.getIntValue("Player1Count");

        int previousCheckpoint = this->checkpoint;
        this->checkpoint = this->kismetModel.getIntValue("Player1CPCount");

        if (this->segment == 0)
        {
            if (this->rings == 1 && previousRings == 0)
            {
                this->start();
            }
        }
        else if (this->segment == 1)
        {
            if (this->rings == 6 && previousRings == 5)
            {
                this->split();
            }
        }
        else if (2 <= this->segment && this->segment <= 13)
        {
            if (this->checkpoint == (previousCheckpoint + 1) && this->checkpoint == (this->segment - 1))
            {
                this->split();
            }
        }
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining" && post)
    {
        this->reset();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset();
    }
}

std::string PanicsAirRaceBeachAutoSplitterComponent::getStartDescription()
{
    return "The timer will start when you cross the first ring.";
}

std::string PanicsAirRaceBeachAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after crossing the 6th ring, crossing each checkpoint, and crossing the finish line (13 splits in total).";
}

std::string PanicsAirRaceBeachAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset when press the \"reset shot\" binding or leave the match.";
}

std::string PanicsAirRaceBeachAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Panic's Air Race Beach Auto Splitter (Debug)" << std::endl;
    ss << "rings = " << this->rings << std::endl;
    ss << "checkpoint = " << this->checkpoint << std::endl;
    return ss.str();
}
