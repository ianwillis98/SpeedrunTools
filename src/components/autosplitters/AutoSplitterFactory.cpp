#include "AutoSplitterFactory.h"
#include "AutoSplitterNull.h"
#include "Dribble2OverhaulAutoSplitter.h"

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
    if (mapName == "dribblechallenge2overhaul")
    {
        return std::make_unique<Dribble2OverhaulAutoSplitter>(this->plugin);
    }
    else
    {
        return std::make_unique<AutoSplitterNull>();
    }
}

bool AutoSplitterFactory::isMapSupported(const std::string &mapName)
{
    return mapName == "dribblechallenge2overhaul";
}
