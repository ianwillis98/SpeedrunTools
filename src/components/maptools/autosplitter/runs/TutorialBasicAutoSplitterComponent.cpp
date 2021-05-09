#include "TutorialBasicAutoSplitterComponent.h"

TutorialBasicAutoSplitterComponent::TutorialBasicAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          isInTutorial(false),
          segment(0)
{

}

void TutorialBasicAutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay" && post)
    {
        this->isInTutorial = true;
    }
    if (eventName == "Function TAGame.GameEvent_Tutorial_TA.Destroyed" && post)
    {
        this->isInTutorial = false;

        if (segment > 0)
        {
            this->segment = 0;
            this->resetTimer();
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
            if (yaw < 16000 || yaw > 16600) return;

            this->segment++;
            this->startTimer();
        }
        else if (this->segment == 6)
        {
            CarWrapper cw = this->plugin->gameWrapper->GetLocalCar();
            if (cw.IsNull()) return;

            int yaw = cw.GetRotation().Yaw;
            if (yaw > 16000 && yaw < 16600) return;

            this->segment++;
            this->splitTimer();
        }
    }
    if (eventName == "Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal" && post)
    {
        if (!this->isInTutorial) return;

        if (1 <= this->segment && this->segment <= 5)
        {
            this->segment++;
            this->splitTimer();
        }
    }
}


std::string TutorialBasicAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "isInTutorial = " << this->isInTutorial << std::endl;
    ss << "segment = " << this->segment << std::endl;
    return ss.str();
}