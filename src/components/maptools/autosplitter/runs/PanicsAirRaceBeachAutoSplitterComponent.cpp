#include "PanicsAirRaceBeachAutoSplitterComponent.h"

PanicsAirRaceBeachAutoSplitterComponent::PanicsAirRaceBeachAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin, "Panic's Air Race Beach"),
          hasUpdatedOnce(false),
          hasUpdatedTwice(false),
          currentRings(0),
          previousRings(0),
          currentCheckpoint(0),
          previousCheckpoint(0)
{

}

void PanicsAirRaceBeachAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
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

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            if (this->previousRings == 0 && this->currentRings == 1)
            {
                this->startTimer();
            }
            if (this->previousRings == 5 && this->currentRings == 6)
            {
                this->splitTimer();
            }
            if (this->previousCheckpoint != this->currentCheckpoint && this->currentCheckpoint > 0)
            {
                this->splitTimer();
            }
            if (this->previousRings != 0 && this->currentRings == 0)
            {
                this->resetTimer();
            }
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;

        if (this->currentRings > 0) this->resetTimer();
    }
}

std::string PanicsAirRaceBeachAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentRings = " << this->currentRings << std::endl;
    ss << "previousRings = " << this->previousRings << std::endl;
    ss << "currentCheckpoint = " << this->currentCheckpoint << std::endl;
    ss << "previousCheckpoint = " << this->previousCheckpoint << std::endl;
    return ss.str();
}
