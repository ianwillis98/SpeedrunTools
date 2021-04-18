//#pragma once
//
//#include "../AutoSplitterBase.h"
//
//class Dribble2OverhaulAutoSplitter : public AutoSplitterBase
//{
//private:
//    bool hasUpdatedOnce;
//    bool hasUpdatedTwice;
//
//    bool previousTiming;
//    bool currentTiming;
//
//    int currentLevel;
//    int previousLevel;
//
//public:
//    explicit Dribble2OverhaulAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);
//
//    bool update() override;
//    void onEvent(const std::string &eventName, bool post, void *params) override;
//
//    bool start() override;
//    bool split() override;
//    bool reset() override;
//};
