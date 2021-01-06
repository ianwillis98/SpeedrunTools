#include "TutorialAdvancedAutoSplitter.h"

TutorialAdvancedAutoSplitter::TutorialAdvancedAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterBase(plugin),
          isInTutorial(false),
          segment(0),
          segment4GoalsScored(0),
          segment5GoalsScored(0)
{

}

void TutorialAdvancedAutoSplitter::onEventReceived(const std::string &eventName, bool post, void *params)
{
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
            if (yaw < -33000 || yaw > -32000) return;

            this->shouldTimerStart = true;
            this->segment++;
        }
        else if (this->segment == 6)
        {
            this->shouldTimerSplit = true;
            this->segment++;
        }
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        if (!this->isInTutorial) return;

        if (this->segment >= 1 && this->segment <= 3)
        {
            this->shouldTimerSplit = true;
            this->segment++;
        }
        else if (this->segment == 4)
        {
            this->segment4GoalsScored++;
            if (this->segment4GoalsScored == 5)
            {
                this->shouldTimerSplit = true;
                this->segment++;
            }
        }
        else if (this->segment == 5)
        {
            this->segment5GoalsScored++;
            if (this->segment5GoalsScored == 3)
            {
                this->shouldTimerSplit = true;
                this->segment++;
            }
        }
    }
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.Destroyed" && post)
    {
        this->isInTutorial = false;

        if (segment == 0) return;

        this->shouldTimerReset = true;
        this->segment = 0;
        this->segment4GoalsScored = 0;
        this->segment5GoalsScored = 0;
    }
}

std::string TutorialAdvancedAutoSplitter::startDescription()
{
    return "The timer will start on \"Welcome to Advanced Tutorial Training!\" popup.";
}

std::string TutorialAdvancedAutoSplitter::splitDescription()
{
    std::stringstream ss;
    ss << "The timer will split after each of six segments:" << std::endl;
    ss << "\t1. Side Dodge (Left)" << std::endl;
    ss << "\t2. Side Dodge (Right)" << std::endl;
    ss << "\t3. Dodge and Momentum" << std::endl;
    ss << "\t4. Double Jump (all five balls scored)" << std::endl;
    ss << "\t5. Rocket Flying (all three balls scored)" << std::endl;
    ss << "\t6. \"Tutorial Completed!\" popup shows" << std::endl;
    return ss.str();
}

std::string TutorialAdvancedAutoSplitter::resetDescription()
{
    std::stringstream ss;
    ss << "The timer will reset whenever the map unloads. This occurs when:" << std::endl;
    ss << "\t- The player exits to the main menu or chooses a different mode/match to play" << std::endl;
    ss << "\t- The player restarts the training" << std::endl;
    ss << "\t- The training ends and the player is teleported to freeplay" << std::endl;
    return ss.str();
}

std::string TutorialAdvancedAutoSplitter::getDebug()
{
    std::stringstream ss;
    ss << "Tutorial Advanced Auto Splitter (Debug)" << std::endl;
    ss << "isInTutorial = " << this->isInTutorial << std::endl;
    ss << "segment = " << this->segment << std::endl;
    ss << "segment4GoalsScored = " << this->segment4GoalsScored << std::endl;
    ss << "segment5GoalsScored = " << this->segment5GoalsScored << std::endl;
    return ss.str();
}

