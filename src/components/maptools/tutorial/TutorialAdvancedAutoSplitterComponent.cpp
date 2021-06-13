#include "TutorialAdvancedAutoSplitterComponent.h"

TutorialAdvancedAutoSplitterComponent::TutorialAdvancedAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          isInTutorial(false),
          segment4GoalsScored(0),
          segment5GoalsScored(0)
{

}

void TutorialAdvancedAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay" && post)
    {
        this->isInTutorial = true;
    }
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.Destroyed" && post)
    {
        this->isInTutorial = false;

        this->segment4GoalsScored = 0;
        this->segment5GoalsScored = 0;
        this->reset();
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        if (!this->isInTutorial) return;

        if (1 <= this->segment && this->segment <= 3)
        {
            this->split();
        }
        else if (this->segment == 4)
        {
            this->segment4GoalsScored++;
            if (this->segment4GoalsScored == 5)
            {
                this->split();
            }
        }
        else if (this->segment == 5)
        {
            this->segment5GoalsScored++;
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (!this->isInTutorial) return;

        if (this->segment == 0)
        {
            CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
            if (cw.IsNull()) return;

            int yaw = cw.GetRotation().Yaw;
            if (-33000 < yaw && yaw < -32000)
            {
                this->start();
            }
        }
        else if (this->segment == 5 && this->segment5GoalsScored >= 3)
        {
            this->split();
        }
    }
}

std::string TutorialAdvancedAutoSplitterComponent::getStartDescription()
{
    return "The timer will start on \"Welcome to Advanced Tutorial Training!\" popup.";
}

std::string TutorialAdvancedAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after completing each section (5 splits in total).";
}

std::string TutorialAdvancedAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset whenever the player resets the tutorial or leaves the match.";
}

std::string TutorialAdvancedAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Tutorial Advanced Auto Splitter (Debug)" << std::endl;
    ss << "isInTutorial = " << this->isInTutorial << std::endl;
    ss << "segment4GoalsScored = " << this->segment4GoalsScored << std::endl;
    ss << "segment5GoalsScored = " << this->segment5GoalsScored << std::endl;
    return ss.str();
}