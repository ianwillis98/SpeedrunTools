//#include "SpeedJumpRings1AutoSplitter.h"
//
//SpeedJumpRings1AutoSplitter::SpeedJumpRings1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin)
//        : AutoSplitterBase(plugin),
//          hasUpdatedOnce(false),
//          hasUpdatedTwice(false),
//          previousRings(0),
//          currentRings(0),
//          shouldStartTimer(false),
//          shouldSplitTimer(false),
//          shouldResetTimer(false)
//{
//
//}
//
//bool SpeedJumpRings1AutoSplitter::update()
//{
//    return this->hasUpdatedTwice;
//}
//
//void SpeedJumpRings1AutoSplitter::onEvent(const std::string &eventName, bool post, void *params)
//{
//    this->shouldStartTimer = false;
//    this->shouldSplitTimer = false;
//    this->shouldResetTimer = false;
//
//    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
//    {
//        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
//        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;
//
//        auto sequence = this->plugin->gameWrapper->GetMainSequence();
//        if (sequence.memory_address == NULL) return;
//
//        auto allVars = sequence.GetAllSequenceVariables(false);
//
//        auto ringsVar = allVars.find("Rings");
//        if (ringsVar == allVars.end()) return;
//
//        this->previousRings = this->currentRings;
//        this->currentRings = ringsVar->second.GetInt();
//
//        if (this->currentRings != this->previousRings)
//        {
//            if (this->currentRings == 0) this->shouldResetTimer = true;
//            else if (this->currentRings == 1) this->shouldStartTimer = true;
//            else if (this->currentRings % 10 == 0 || this->currentRings == 162) this->shouldSplitTimer = true;
//        }
//    }
//    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
//    {
//        if (this->currentRings > 0)
//        {
//            this->shouldResetTimer = true;
//        }
//    }
//    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
//    {
//        this->hasUpdatedOnce = false;
//        this->hasUpdatedTwice = false;
//
//        if (this->currentRings > 0) this->shouldResetTimer = true;
//    }
//}
//
//bool SpeedJumpRings1AutoSplitter::supportsStart()
//{
//    return true;
//}
//
//bool SpeedJumpRings1AutoSplitter::supportsSplit()
//{
//    return true;
//}
//
//bool SpeedJumpRings1AutoSplitter::supportsReset()
//{
//    return true;
//}
//
//bool SpeedJumpRings1AutoSplitter::start()
//{
//    return this->shouldStartTimer;
//}
//
//bool SpeedJumpRings1AutoSplitter::split()
//{
//    return this->shouldSplitTimer;
//}
//
//bool SpeedJumpRings1AutoSplitter::reset()
//{
//    return this->shouldResetTimer;
//}
//
//std::string SpeedJumpRings1AutoSplitter::getDebug()
//{
//    std::stringstream ss;
//    ss << "Speed Jump Rings 1 Auto Splitter (Debug)" << std::endl;
//    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
//    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
//    ss << "previousRings = " << this->previousRings << std::endl;
//    ss << "currentRings = " << this->currentRings << std::endl;
//    return ss.str();
//}
//
//std::string SpeedJumpRings1AutoSplitter::startDescription()
//{
//    return AutoSplitterBase::startDescription();
//}
//
//std::string SpeedJumpRings1AutoSplitter::splitDescription()
//{
//    return AutoSplitterBase::splitDescription();
//}
//
//std::string SpeedJumpRings1AutoSplitter::resetDescription()
//{
//    return AutoSplitterBase::resetDescription();
//}
