#include "PanicsAirRaceBeachAutoSplitter.h"

PanicsAirRaceBeachAutoSplitter::PanicsAirRaceBeachAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          previousRings(0),
          currentRings(0),
          previousCheckpoint(0),
          currentCheckpoint(0)
{

}

void PanicsAirRaceBeachAutoSplitter::onEventReceived(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto rings = allVars.find("Player1Count");
        if (rings == allVars.end()) return;

        this->previousRings = this->currentRings;
        this->currentRings = rings->second.GetInt();

        auto checkpoint = allVars.find("Player1CPCount");
        if (checkpoint == allVars.end()) return;

        this->previousCheckpoint = this->currentCheckpoint;
        this->currentCheckpoint = checkpoint->second.GetInt();

        if (this->previousRings == 0 && this->currentRings == 1)
        {
            this->shouldTimerStart = true;
        }
        if (this->previousRings == 5 && this->currentRings == 6)
        {
            this->shouldTimerSplit = true;
        }
        if (this->previousCheckpoint != this->currentCheckpoint && this->currentCheckpoint > 0)
        {
            this->shouldTimerSplit = true;
        }
        if (this->previousRings != 0 && this->currentRings == 0)
        {
            this->shouldTimerReset = true;
        }
    }
}

std::string PanicsAirRaceBeachAutoSplitter::startDescription()
{
    return "The timer will start after entering the first ring.";
}

std::string PanicsAirRaceBeachAutoSplitter::splitDescription()
{
    std::stringstream ss;
    ss << "The timer will split after each of 13 segments:" << std::endl;
    ss << "\t1. Entering the sixth ring" << std::endl;
    ss << "\t2. Checkpoint 1" << std::endl;
    ss << "\t3. Checkpoint 2" << std::endl;
    ss << "\t4. Checkpoint 3" << std::endl;
    ss << "\t5. Checkpoint 4" << std::endl;
    ss << "\t6. Checkpoint 5" << std::endl;
    ss << "\t7. Checkpoint 6" << std::endl;
    ss << "\t8. Checkpoint 7" << std::endl;
    ss << "\t9. Checkpoint 8" << std::endl;
    ss << "\t10. Checkpoint 9" << std::endl;
    ss << "\t11. Checkpoint 10" << std::endl;
    ss << "\t12. Checkpoint 11" << std::endl;
    ss << "\t13. Crossing the finish line" << std::endl;
    return ss.str();
}

std::string PanicsAirRaceBeachAutoSplitter::resetDescription()
{
    return AutoSplitterBase::resetDescription();
}

std::string PanicsAirRaceBeachAutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Panic's Air Race Beach (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "previousRings = " << this->previousRings << std::endl;
    ss << "currentRings = " << this->currentRings << std::endl;
    ss << "previousCheckpoint = " << this->previousCheckpoint << std::endl;
    ss << "currentCheckpoint = " << this->currentCheckpoint << std::endl;
    return ss.str();
}
