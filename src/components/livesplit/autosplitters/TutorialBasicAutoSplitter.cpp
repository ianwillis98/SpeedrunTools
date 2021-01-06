#include "TutorialBasicAutoSplitter.h"

TutorialBasicAutoSplitter::TutorialBasicAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          isInTutorial(false),
          shouldStartTimer(false),
          shouldSplitTimer(false),
          shouldResetTimer(false),
          segment(0)
{

}

void TutorialBasicAutoSplitter::onEvent(const std::string &eventName, bool post, void *params)
{
    this->shouldStartTimer = false;
    this->shouldSplitTimer = false;
    this->shouldResetTimer = false;

    if (eventName == "Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay" && post)
    {
        this->isInTutorial = true;
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (!this->isInTutorial) return;

        if (this->segment == 0)
        {
            CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
            if (cw.IsNull()) return;

            int yaw = cw.GetRotation().Yaw;
            if (yaw < 16000 || yaw > 16600) return;

            this->shouldStartTimer = true;
            this->segment++;
        }
        else if (this->segment == 6)
        {
            CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
            if (cw.IsNull()) return;

            int yaw = cw.GetRotation().Yaw;
            if (yaw > 16000 && yaw < 16600) return;

            this->shouldSplitTimer = true;
            this->segment++;
        }
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        if (!this->isInTutorial) return;
        if (this->segment < 1 || this->segment > 5) return;

        this->shouldSplitTimer = true;
        this->segment++;
    }
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.Destroyed" && post)
    {
        this->isInTutorial = false;

        if (segment == 0) return;

        this->shouldResetTimer = true;
        this->segment = 0;
    }
}

bool TutorialBasicAutoSplitter::supportsAutoStart()
{
    return true;
}

bool TutorialBasicAutoSplitter::supportsAutoSplit()
{
    return true;
}

bool TutorialBasicAutoSplitter::supportsAutoReset()
{
    return true;
}

bool TutorialBasicAutoSplitter::shouldTimerStart()
{
    return this->shouldStartTimer;
}

bool TutorialBasicAutoSplitter::shouldTimerSplit()
{
    return this->shouldSplitTimer;
}

bool TutorialBasicAutoSplitter::shouldTimerReset()
{
    return this->shouldResetTimer;
}

std::string TutorialBasicAutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Tutorial Basic Auto Splitter (Debug)" << std::endl;
    ss << "isInTutorial = " << this->isInTutorial << std::endl;
    ss << "segment = " << this->segment << std::endl;
    return ss.str();
}

std::string TutorialBasicAutoSplitter::autoStartDescription()
{
    return "The timer will start on \"Welcome to Tutorial Training!\" popup.";
}

std::string TutorialBasicAutoSplitter::autoSplitDescription()
{
    std::stringstream ss;
    ss << "The timer will split after each of six segments:" << std::endl;
    ss << "\t1. Movement" << std::endl;
    ss << "\t2. Jump" << std::endl;
    ss << "\t3. Dodge" << std::endl;
    ss << "\t4. Rocket Boost" << std::endl;
    ss << "\t5. Locating the Ball" << std::endl;
    ss << "\t6. Powerslide" << std::endl;
    return ss.str();
}

std::string TutorialBasicAutoSplitter::autoResetDescription()
{
    std::stringstream ss;
    ss << "The timer will reset whenever the map unloads. This occurs when:" << std::endl;
    ss << "\t- The player exits to the main menu or chooses a different mode/match to play" << std::endl;
    ss << "\t- The player restarts the training" << std::endl;
    ss << "\t- The training ends and the player is teleported to freeplay" << std::endl;
    return ss.str();
}
