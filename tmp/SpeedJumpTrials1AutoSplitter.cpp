#include "SpeedJumpTrials1AutoSplitter.h"

SpeedJumpTrials1AutoSplitter::SpeedJumpTrials1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false)
{

}

void SpeedJumpTrials1AutoSplitter::onEventReceived(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto levelVar = allVars.find("Level");
        if (levelVar == allVars.end()) return;
        this->previousLevel = this->currentLevel;
        this->currentLevel = levelVar->second.GetInt();

        auto minVar = allVars.find("emin");
        if (minVar == allVars.end()) return;
        this->currentMin = minVar->second.GetInt();

        auto secVar = allVars.find("esec");
        if (secVar == allVars.end()) return;
        this->previousSec = this->currentSec;
        this->currentSec = secVar->second.GetInt();

        auto resetVar = allVars.find("Reset");
        if (resetVar == allVars.end()) return;
        this->currentReset = resetVar->second.GetBool();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->currentSec == 1 && this->previousSec == 0 && this->currentMin == 0) this->shouldTimerStart = true;
            if (this->currentLevel != this->previousLevel && this->currentLevel > 0) this->shouldTimerSplit = true;
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        this->plugin->cvarManager->log("herereerererer");
    }
}

std::string SpeedJumpTrials1AutoSplitter::startDescription()
{
    return AutoSplitterBase::startDescription();
}

std::string SpeedJumpTrials1AutoSplitter::splitDescription()
{
    return AutoSplitterBase::splitDescription();
}

std::string SpeedJumpTrials1AutoSplitter::resetDescription()
{
    return AutoSplitterBase::resetDescription();
}

std::string SpeedJumpTrials1AutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 1 Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    ss << "currentMin = " << this->currentMin << std::endl;
    ss << "currentSec = " << this->currentSec << std::endl;
    ss << "previousSec = " << this->previousSec << std::endl;
    ss << "currentReset = " << this->currentReset << std::endl;
    return ss.str();
}
