#include "AirDribbleHoopsAutoSplitter.h"

AirDribbleHoopsAutoSplitter::AirDribbleHoopsAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentTimer(false),
          previousTimer(false),
          currentLevel(0),
          previousLevel(0)
{

}

void AirDribbleHoopsAutoSplitter::onEventReceived(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto timerVar = allVars.find("Timer");
        if (timerVar == allVars.end()) return;

        this->previousTimer = this->currentTimer;
        this->currentTimer = timerVar->second.GetBool();

        auto levelVar = allVars.find("Level");
        if (levelVar == allVars.end()) return;

        this->previousLevel = this->currentLevel;
        this->currentLevel = levelVar->second.GetInt();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->currentTimer && !this->previousTimer) this->shouldTimerStart = true;
            if (this->currentLevel != this->previousLevel) this->shouldTimerSplit = true;
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;
    }
}

bool AirDribbleHoopsAutoSplitter::supportsReset()
{
    return false;
}

std::string AirDribbleHoopsAutoSplitter::startDescription()
{
    return "The timer will start at the selection of 'Speedrun Mode'.";
}

std::string AirDribbleHoopsAutoSplitter::splitDescription()
{
    return "The timer will split after the completion of each level.";
}

std::string AirDribbleHoopsAutoSplitter::resetDescription()
{
    return "This auto splitter does not support auto reset.";
}

std::string AirDribbleHoopsAutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Air Dribble Hoops Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentTimer = " << this->currentTimer << std::endl;
    ss << "previousTimer = " << this->previousTimer << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    return ss.str();
}
