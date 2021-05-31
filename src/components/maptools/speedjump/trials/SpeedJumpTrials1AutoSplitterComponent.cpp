//#include "SpeedJumpTrials1AutoSplitterComponent.h"
//
//SpeedJumpTrials1AutoSplitterComponent::SpeedJumpTrials1AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
//        : AutoSplitterComponent(plugin),
//          hasUpdatedOnce(),
//          hasUpdatedTwice(),
//          currentLevel(),
//          previousLevel(),
//          currentReset()
//{
//
//}
//
//void SpeedJumpTrials1AutoSplitterComponent::onEnable()
//{
//    this->hasUpdatedOnce = false;
//    this->hasUpdatedTwice = false;
//}
//
//void SpeedJumpTrials1AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
//{
//    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
//    {
//        auto sequence = this->plugin->gameWrapper->GetMainSequence();
//        if (sequence.memory_address == NULL) return;
//
//        auto allVars = sequence.GetAllSequenceVariables(false);
//
//        auto levelVar = allVars.find("Level");
//        if (levelVar == allVars.end()) return;
//
//        this->previousLevel = this->currentLevel;
//        this->currentLevel = levelVar->second.GetInt();
//
//        auto resetVar = allVars.find("Reset");
//        if (resetVar == allVars.end()) return;
//
//        this->currentReset = resetVar->second.GetBool();
//
//        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
//        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;
//
//        if (this->hasUpdatedTwice)
//        {
//            if (this->segment == 0)
//            {
//                CarWrapper carWrapper = this->plugin->gameWrapper->GetLocalCar();
//                if (!carWrapper.IsNull())
//                {
//                    if (carWrapper.GetLocation().X >= 1408.0f) this->startTimer();
//                }
//            }
//            else if (1 <= this->segment && this->segment <= 9)
//            {
//                if (this->currentLevel == (this->previousLevel + 1)) this->splitTimer();
//            }
//            else if (this->segment == 10)
//            {
//                if (this->currentLevel == 0 && this->previousLevel == 10) this->splitTimer();
//            }
//        }
//    }
//    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
//    {
//        if (this->currentReset) this->resetTimer();
//    }
//    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
//    {
//        this->hasUpdatedOnce = false;
//        this->hasUpdatedTwice = false;
//        if (this->segment > 0) this->resetTimer();
//    }
//}
