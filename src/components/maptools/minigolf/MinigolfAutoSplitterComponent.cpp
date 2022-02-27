#include "MinigolfAutoSplitterComponent.h"

MinigolfAutoSplitterComponent::MinigolfAutoSplitterComponent(NetcodePlugin* plugin)
    : AutoSplitterComponent(plugin),
    mapStarted(false)
{

}

void MinigolfAutoSplitterComponent::onEnable()
{
    this->mapStarted = false;
}

void MinigolfAutoSplitterComponent::update(const std::string& eventName, bool post, void* params)
{
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.InitGame" && post)
    {
        this->mapStarted = true;
    }
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        if (this->segment != 0 || !this->mapStarted) return;
        auto car = this->plugin->gameWrapper->GetLocalCar();
        if (!car) return;
        if (car.GetVelocity().magnitude() != 0)
            this->start();
    }
    if (eventName == "Function TAGame.Ball_TA.Explode" && post)
    {
        if (1 <= this->segment && this->segment <= 9) {
            this->split();
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->mapStarted = false;
        this->reset();
    }
}

std::string MinigolfAutoSplitterComponent::getStartDescription()
{
    return "The timer will start when the map loads.";
}

std::string MinigolfAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after a goal is scored (9 splits in total).";
}

std::string MinigolfAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset after leaving the match.";
}

std::string MinigolfAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Minigolf Auto Splitter (Debug)" << std::endl;
    ss << "mapStarted = " << this->mapStarted << std::endl;
    return ss.str();
}