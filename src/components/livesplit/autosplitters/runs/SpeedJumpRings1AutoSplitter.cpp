#include "SpeedJumpRings1AutoSplitter.h"

SpeedJumpRings1AutoSplitter::SpeedJumpRings1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentRings(0),
          previousRings(0)
{

}

void SpeedJumpRings1AutoSplitter::onEventReceived(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto ringsVar = allVars.find("Rings");
        if (ringsVar == allVars.end()) return;

        this->previousRings = this->currentRings;
        this->currentRings = ringsVar->second.GetInt();

        if (this->currentRings != this->previousRings)
        {
            if (this->currentRings == 0) this->shouldTimerReset = true;
            else if (this->currentRings == 1) this->shouldTimerStart = true;
            else if (this->currentRings % 10 == 0) this->shouldTimerSplit = true;
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->currentRings >= 161) this->shouldTimerSplit = true;
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
    {
        if (this->currentRings > 0) this->resetRingsKismetToZero();

    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;

        if (this->currentRings > 0) this->shouldTimerReset = true;
    }
}

std::string SpeedJumpRings1AutoSplitter::startDescription()
{
    return AutoSplitterBase::startDescription();
}

std::string SpeedJumpRings1AutoSplitter::splitDescription()
{
    return AutoSplitterBase::splitDescription();
}

std::string SpeedJumpRings1AutoSplitter::resetDescription()
{
    return AutoSplitterBase::resetDescription();
}

std::string SpeedJumpRings1AutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 1 Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentRings = " << this->currentRings << std::endl;
    ss << "previousRings = " << this->previousRings << std::endl;
    return ss.str();
}

void SpeedJumpRings1AutoSplitter::resetRingsKismetToZero()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto allVars = sequence.GetAllSequenceVariables(false);

    auto rings = allVars.find("Rings");
    if (rings == allVars.end()) return;

    rings->second.SetInt(0);
}
