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
            if (this->rings == (previousRings + 1) && (this->rings % 10) == 0 && this->rings == ((this->segment + 1) * 10))
            {
                this->split();
            }
        }
//        else if (this->segment == 17)
//        {
//            if (this->rings == 162 && previousRings != 162)
//            {
//                this->split();
//            }
//        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->segment == 17)
        {
            if (this->rings >= 161)
            {
                // test what rings and previousRings are
                this->split();
            }
        }
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
    {
        this->resetRingsKismetToZero();
        this->reset();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        if (this->segment > 0) this->reset();
    }
}

std::string SpeedJumpRings1AutoSplitterComponent::getStartDescription()
{
    return "The timer will start after passing the first ring.";
}

std::string SpeedJumpRings1AutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after every 10 rings passed and after passing the final ring (17 splits in total).";
}

std::string SpeedJumpRings1AutoSplitterComponent::getResetDescription()
{
    return "The timer will reset when the player presses the 'Reset Shot' binding or leaves the map.";
}

std::string SpeedJumpRings1AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 1 Auto Splitter (Debug)" << std::endl;
    ss << "rings = " << this->rings << std::endl;
    return ss.str();
}

void SpeedJumpRings1AutoSplitterComponent::resetRingsKismetToZero()
{
    this->kismetModel.setIntValue("Rings", 0);
}
