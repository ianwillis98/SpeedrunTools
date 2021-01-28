#include "LethsGiantRingsAutoSplitter.h"

LethsGiantRingsAutoSplitter::LethsGiantRingsAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentTiming(false),
          previousTiming(false),
          currentLevel(0),
          previousLevel(0)
{

}

void LethsGiantRingsAutoSplitter::onEventReceived(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto timingVar = allVars.find("Timing");
        if (timingVar == allVars.end()) return;

        this->previousTiming = this->currentTiming;
        this->currentTiming = timingVar->second.GetBool();

        auto levelVar = allVars.find("Level");
        if (levelVar == allVars.end()) return;

        this->previousLevel = this->currentLevel;
        this->currentLevel = levelVar->second.GetInt();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->currentTiming && !this->previousTiming) this->shouldTimerStart = true;
            if (this->currentLevel != this->previousLevel) this->shouldTimerSplit = true;
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;
    }
}

bool LethsGiantRingsAutoSplitter::supportsReset()
{
    return false;
}

std::string LethsGiantRingsAutoSplitter::startDescription()
{
    return "The timer will start when the map's timer starts.";
}

std::string LethsGiantRingsAutoSplitter::splitDescription()
{
    return "The timer will split after completing each level.";
}

std::string LethsGiantRingsAutoSplitter::resetDescription()
{
    return "This auto splitter does not support auto reset.";
}

std::string LethsGiantRingsAutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Air Dribble Hoops Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentTiming = " << this->currentTiming << std::endl;
    ss << "previousTiming = " << this->previousTiming << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    return ss.str();
}