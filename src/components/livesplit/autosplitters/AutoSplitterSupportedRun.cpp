#include "AutoSplitterSupportedRun.h"

#include <utility>

const AutoSplitterSupportedRun AutoSplitterSupportedRun::NONE("None");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::TUTORIAL_BASIC("Tutorial Basic");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::TUTORIAL_ADVANCED("Tutorial Advanced");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::PANICS_AIR_RACE_BEACH("Panic's Air Race Beach");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::SPEED_JUMP_RINGS_1("Speed Jump: Rings 1");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::AIR_DRIBBLE_HOOPS("Air Dribble Hoops");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::LETHS_GIANT_RINGS("Leth's Giant Rings");

AutoSplitterSupportedRun::AutoSplitterSupportedRun(std::string runName) : runName(std::move(runName))
{

}
