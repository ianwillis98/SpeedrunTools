#include "SpeedJumpRings1AutoSplitterComponent.h"

SpeedJumpRings1AutoSplitterComponent::SpeedJumpRings1AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          rings()
{

}

void SpeedJumpRings1AutoSplitterComponent::onEnable()
{
    this->rings = this->kismetModel.getIntValue("Rings");
}

void SpeedJumpRings1AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        int previousRings = this->rings;
        this->rings = this->kismetModel.getIntValue("Rings");

        if (this->segment == 0)
        {
            if (this->rings == 1 && previousRings != 1)
            {
                this->start();
            }
        }
        else if (1 <= this->segment && this->segment <= 16)
        {
            if (this->rings == (previousRings + 1) && (this->rings % 10) == 0 && this->rings == (this->segment * 10))
            {
                this->split();
            }
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->segment == 17)
        {
            // rings is 161
            this->split();
        }
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
    {
        this->kismetModel.setIntValue("Rings", 0); // in case they reset when rings is 1
        this->reset();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset();
    }
}

std::string SpeedJumpRings1AutoSplitterComponent::getStartDescription()
{
    return "The timer will start after entering the first ring.";
}

std::string SpeedJumpRings1AutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after entering every 10th ring and after entering the final ring (17 splits in total, 162 rings).";
}

std::string SpeedJumpRings1AutoSplitterComponent::getResetDescription()
{
    return "The timer will reset when the player presses the 'Reset Shot' binding or leaves the match.";
}

std::string SpeedJumpRings1AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 1 Auto Splitter (Debug)" << std::endl;
    ss << "rings = " << this->rings << std::endl;
    return ss.str();
}
