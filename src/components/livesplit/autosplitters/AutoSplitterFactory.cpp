#include "AutoSplitterFactory.h"
#include "AutoSplitterSupportedRun.h"
#include "runs/TutorialBasicAutoSplitter.h"
#include "runs/TutorialAdvancedAutoSplitter.h"
#include "runs/PanicsAirRaceBeachAutoSplitter.h"
#include "runs/SpeedJumpRings1AutoSplitter.h"
#include "runs/AirDribbleHoopsAutoSplitter.h"
#include "runs/LethsGiantRingsAutoSplitter.h"
#include "runs/SpeedJumpTrials1AutoSplitter.h"

AutoSplitterFactory::AutoSplitterFactory(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

AutoSplitterFactory &AutoSplitterFactory::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static AutoSplitterFactory instance(plugin);
    return instance;
}

std::unique_ptr<AutoSplitter> AutoSplitterFactory::getAutoSplitterForRun(const std::string &runName)
{
    if (runName == AutoSplitterSupportedRun::TUTORIAL_BASIC.runName)
    {
        return std::make_unique<TutorialBasicAutoSplitter>(this->plugin);
    }
    else if (runName == AutoSplitterSupportedRun::TUTORIAL_ADVANCED.runName)
    {
        return std::make_unique<TutorialAdvancedAutoSplitter>(this->plugin);
    }
    else if (runName == AutoSplitterSupportedRun::PANICS_AIR_RACE_BEACH.runName)
    {
        return std::make_unique<PanicsAirRaceBeachAutoSplitter>(this->plugin);
    }
    else if (runName == AutoSplitterSupportedRun::SPEED_JUMP_RINGS_1.runName)
    {
        return std::make_unique<SpeedJumpRings1AutoSplitter>(this->plugin);
    }
    else if (runName == AutoSplitterSupportedRun::AIR_DRIBBLE_HOOPS.runName)
    {
        return std::make_unique<AirDribbleHoopsAutoSplitter>(this->plugin);
    }
    else if (runName == AutoSplitterSupportedRun::LETHS_GIANT_RINGS.runName)
    {
        return std::make_unique<LethsGiantRingsAutoSplitter>(this->plugin);
    }
    else if (runName == AutoSplitterSupportedRun::SPEED_JUMP_TRIALS_1.runName)
    {
        return std::make_unique<SpeedJumpTrials1AutoSplitter>(this->plugin);
    }

    return nullptr;
}
