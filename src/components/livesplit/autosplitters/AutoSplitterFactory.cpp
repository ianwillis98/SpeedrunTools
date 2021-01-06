#include "AutoSplitterFactory.h"
#include "AutoSplitterSupportedRun.h"
#include "runs/TutorialBasicAutoSplitter.h"
#include "runs/TutorialAdvancedAutoSplitter.h"

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

    return nullptr;
}
