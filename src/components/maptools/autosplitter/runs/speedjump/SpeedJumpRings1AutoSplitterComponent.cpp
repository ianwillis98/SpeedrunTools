#include "SpeedJumpRings1AutoSplitterComponent.h"

SpeedJumpRings1AutoSplitterComponent::SpeedJumpRings1AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentRings(),
          previousRings()
{

}

void SpeedJumpRings1AutoSplitterComponent::onEnable()
{
    this->hasUpdatedOnce = false;
    this->hasUpdatedTwice = false;
    this->resetRingsKismetToZero();
}

void SpeedJumpRings1AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto ringsVar = allVars.find("Rings");
        if (ringsVar == allVars.end()) return;

        this->previousRings = this->currentRings;
        this->currentRings = ringsVar->second.GetInt();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->currentRings != this->previousRings && this->currentRings == 1) this->startTimer();
            if (this->currentRings != this->previousRings && this->currentRings > 1 & this->currentRings % 10 == 0) this->splitTimer();
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->currentRings >= 161) this->splitTimer();
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
    {
        this->resetRingsKismetToZero();
        this->resetTimer();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;

        if (this->currentRings > 0) this->resetTimer();
    }
}

std::string SpeedJumpRings1AutoSplitterComponent::getStartDescription()
{
    return "The timer will start after passing the first ring.";
}

std::string SpeedJumpRings1AutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after every 10 rings passed and after passing the final ring (162 rings in total).";
}

std::string SpeedJumpRings1AutoSplitterComponent::getResetDescription()
{
    return "The timer will reset when the player presses the 'Reset Shot' binding or leaves the map.";
}

std::string SpeedJumpRings1AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 1 Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentRings = " << this->currentRings << std::endl;
    ss << "previousRings = " << this->previousRings << std::endl;
    return ss.str();
}

void SpeedJumpRings1AutoSplitterComponent::resetRingsKismetToZero()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto allVars = sequence.GetAllSequenceVariables(false);

    auto rings = allVars.find("Rings");
    if (rings == allVars.end()) return;

    rings->second.SetInt(0);
}
