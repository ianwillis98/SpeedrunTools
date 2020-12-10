#include "Dribble2OverhaulAutoSplitter.h"

Dribble2OverhaulAutoSplitter::Dribble2OverhaulAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitter(plugin), hasUpdatedOnce(false), hasUpdatedTwice(false), previousTiming(false), previousLevel(0), currentTiming(false),
          currentLevel(0)
{

}

std::string Dribble2OverhaulAutoSplitter::mapName()
{
    return "dribblechallenge2overhaul";
}

void Dribble2OverhaulAutoSplitter::reset()
{
    this->hasUpdatedOnce = false;
    this->hasUpdatedTwice = false;
}

bool Dribble2OverhaulAutoSplitter::update()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return false;

    auto allVars = sequence.GetAllSequenceVariables(false);

    auto levelVar = allVars.find("Level");
    if (levelVar == allVars.end()) return false;

    auto timingVar = allVars.find("Timing");
    if (timingVar == allVars.end()) return false;

    this->previousTiming = this->currentTiming;
    this->previousLevel = this->currentLevel;

    this->currentTiming = timingVar->second.GetBool();
    this->currentLevel = levelVar->second.GetInt();

    if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
    if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

    return this->hasUpdatedTwice;
}

bool Dribble2OverhaulAutoSplitter::shouldStartTimer()
{
    return currentTiming && !previousTiming && (currentLevel == 1);
}

bool Dribble2OverhaulAutoSplitter::shouldSplitTimer()
{
    bool middleLevelPassed = this->currentLevel == this->previousLevel + 1;
    bool finalLevelPassed = (this->currentLevel == 1) && (this->previousLevel == 30);

    return this->currentTiming && (middleLevelPassed || finalLevelPassed);
}
