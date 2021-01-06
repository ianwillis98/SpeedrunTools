#include "AutoSplitterFactory.h"
#include "autosplitters/Dribble2OverhaulAutoSplitter.h"
#include "autosplitters/TutorialBasicAutoSplitter.h"
#include "autosplitters/NullAutoSplitter.h"
#include "autosplitters/TutorialAdvancedAutoSplitter.h"
#include "autosplitters/SpeedJumpRings1AutoSplitter.h"

AutoSplitterFactory::AutoSplitterFactory(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

AutoSplitterFactory &AutoSplitterFactory::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static AutoSplitterFactory instance(plugin);
    return instance;
}

std::unique_ptr<AutoSplitter> AutoSplitterFactory::getAutoSplitterForRun(const std::string &runTitle)
{
    if (runTitle == AutoSplitterRunTemp::Dribble2Overhaul.runName)
    {
        return std::make_unique<Dribble2OverhaulAutoSplitter>(this->plugin);
    }
    else if (runTitle == AutoSplitterRunTemp::TutorialBasic.runName)
    {
        return std::make_unique<TutorialBasicAutoSplitter>(this->plugin);
    }
    else if (runTitle == AutoSplitterRunTemp::TutorialAdvanced.runName)
    {
        return std::make_unique<TutorialAdvancedAutoSplitter>(this->plugin);
    }
    else if (runTitle == AutoSplitterRunTemp::SpeedJumpRings1_100.runName)
    {
        return std::make_unique<SpeedJumpRings1AutoSplitter>(this->plugin);
    }

    return std::make_unique<NullAutoSplitter>();
}

const AutoSplitterRunTemp AutoSplitterRunTemp::Null = AutoSplitterRunTemp("None");
const AutoSplitterRunTemp AutoSplitterRunTemp::Dribble2Overhaul = AutoSplitterRunTemp("Dribble 2 Overhaul");
const AutoSplitterRunTemp AutoSplitterRunTemp::TutorialBasic = AutoSplitterRunTemp("Tutorial Basic");
const AutoSplitterRunTemp AutoSplitterRunTemp::TutorialAdvanced = AutoSplitterRunTemp("Tutorial Advanced");
const AutoSplitterRunTemp AutoSplitterRunTemp::SpeedJumpRings1_100 = AutoSplitterRunTemp("Speed Jump: Rings 1");

const std::vector<AutoSplitterRunTemp> AutoSplitterRunTemp::runs = {
        AutoSplitterRunTemp::Null,
        AutoSplitterRunTemp::Dribble2Overhaul,
        AutoSplitterRunTemp::TutorialBasic,
        AutoSplitterRunTemp::TutorialAdvanced,
        AutoSplitterRunTemp::SpeedJumpRings1_100,
};

const char *AutoSplitterRunTemp::runNames[] = {
        AutoSplitterRunTemp::Null.runName.c_str(),
        AutoSplitterRunTemp::Dribble2Overhaul.runName.c_str(),
        AutoSplitterRunTemp::TutorialBasic.runName.c_str(),
        AutoSplitterRunTemp::TutorialAdvanced.runName.c_str(),
        AutoSplitterRunTemp::SpeedJumpRings1_100.runName.c_str(),
};

AutoSplitterRunTemp::AutoSplitterRunTemp(std::string runName)
        : runName(std::move(runName))
{

}
