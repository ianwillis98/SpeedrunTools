#include "AutoSplitterSupportedRun.h"

#include <utility>

const AutoSplitterSupportedRun AutoSplitterSupportedRun::NONE("None");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::TUTORIAL_BASIC("Tutorial Basic");
const AutoSplitterSupportedRun AutoSplitterSupportedRun::TUTORIAL_ADVANCED("Tutorial Advanced");

AutoSplitterSupportedRun::AutoSplitterSupportedRun(std::string runName) : runName(std::move(runName))
{

}
