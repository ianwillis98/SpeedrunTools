#include "TutorialBasicAutoSplitter.h"

TutorialBasicAutoSplitter::TutorialBasicAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin) : AutoSplitterBase(plugin)
{

}

bool TutorialBasicAutoSplitter::update()
{

    return true;
}

void TutorialBasicAutoSplitter::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.OnInit Delayed" && post)
    {
        this->plugin->cvarManager->log("map is " + this->plugin->gameWrapper->GetCurrentMap());
        this->didTutorialStart = true;
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        this->plugin->cvarManager->log("tut scored");
        this->didScoreGoal = true;
    }
}

bool TutorialBasicAutoSplitter::shouldTimerStart()
{
    bool shouldTimerStart = this->didTutorialStart;
    this->didTutorialStart = false;
    return shouldTimerStart;
}

bool TutorialBasicAutoSplitter::shouldTimerSplit()
{
    return false;
}

bool TutorialBasicAutoSplitter::shouldTimerReset()
{
    return false;
}
