#include "AutoSplitterFactory.h"
#include "Dribble2OverhaulAutoSplitter.h"
#include "TutorialBasicAutoSplitter.h"
#include "NullAutoSplitter.h"

AutoSplitterFactory::AutoSplitterFactory(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

AutoSplitterFactory &AutoSplitterFactory::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static AutoSplitterFactory instance(plugin);
    return instance;
}

std::unique_ptr<AutoSplitter> AutoSplitterFactory::getAutoSplitterForMap(const std::string &mapName)
{
    if (mapName == AutoSplitterMap::Dribble2Overhaul.mapName)
    {
        return std::make_unique<Dribble2OverhaulAutoSplitter>(this->plugin);
    }
    else if (mapName == AutoSplitterMap::TutorialBasic.mapName)
    {
        return std::make_unique<TutorialBasicAutoSplitter>(this->plugin);
    }

    return std::make_unique<NullAutoSplitter>();
}

const AutoSplitterMap AutoSplitterMap::Null = AutoSplitterMap("None", "");
const AutoSplitterMap AutoSplitterMap::Dribble2Overhaul = AutoSplitterMap("Dribble 2 Overhaul", "dribblechallenge2overhaul");
const AutoSplitterMap AutoSplitterMap::TutorialBasic = AutoSplitterMap("Tutorial Basic", "Park_P");

const std::vector<AutoSplitterMap> AutoSplitterMap::maps = {
        AutoSplitterMap::Null,
        AutoSplitterMap::Dribble2Overhaul,
        AutoSplitterMap::TutorialBasic
};

const char *AutoSplitterMap::mapTitles[] = {
        AutoSplitterMap::Null.mapTitle.c_str(),
        AutoSplitterMap::Dribble2Overhaul.mapTitle.c_str(),
        AutoSplitterMap::TutorialBasic.mapTitle.c_str()
};

const char *AutoSplitterMap::mapNames[] = {
        AutoSplitterMap::Null.mapName.c_str(),
        AutoSplitterMap::Dribble2Overhaul.mapName.c_str(),
        AutoSplitterMap::TutorialBasic.mapName.c_str()
};

AutoSplitterMap::AutoSplitterMap(std::string mapTitle, std::string mapName)
        : mapTitle(std::move(mapTitle)), mapName(std::move(mapName))
{

}
