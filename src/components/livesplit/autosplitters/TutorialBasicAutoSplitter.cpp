#include "TutorialBasicAutoSplitter.h"

TutorialBasicAutoSplitter::TutorialBasicAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          shouldStartTimer(false),
          shouldSplitTimer(false),
          shouldResetTimer(false),
          level(0)
{

}

bool TutorialBasicAutoSplitter::update()
{
    return this->plugin->gameWrapper->GetCurrentMap() == "Park_P";
}

void TutorialBasicAutoSplitter::onEvent(const std::string &eventName, bool post, void *params)
{
    if (this->plugin->gameWrapper->GetCurrentMap() != "Park_P") return;

    if (eventName == "Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay Delayed" && post)
    {
        if (this->level != 0)
        {
            this->shouldResetTimer = true;
            this->level = 0;
        }
        else
        {
            this->shouldStartTimer = true;
            this->level++;
        }
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        if (this->level < 1 || this->level > 5) return;

        this->shouldSplitTimer = true;
        this->level++;
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->level != 6) return;

        CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
        if (cw.IsNull()) return;

        int yaw = cw.GetRotation().Yaw;
        if (yaw > 16000 && yaw < 16600) return;

        this->shouldSplitTimer = true;
        this->level++;
    }
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.Destroyed" && post)
    {
        if (level == 0) return;

        this->shouldResetTimer = true;
        this->level = 0;
    }
}

bool TutorialBasicAutoSplitter::shouldTimerStart()
{
    bool temp = this->shouldStartTimer;
    this->shouldStartTimer = false;
    return temp;
}

bool TutorialBasicAutoSplitter::shouldTimerSplit()
{
    bool temp = this->shouldSplitTimer;
    this->shouldSplitTimer = false;
    return temp;
}

bool TutorialBasicAutoSplitter::shouldTimerReset()
{
    bool temp = this->shouldResetTimer;
    this->shouldResetTimer = false;
    return temp;
}
