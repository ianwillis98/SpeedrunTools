//#pragma once
//
//#include "../AutoSplitterBase.h"
//
//class SpeedJumpRings1AutoSplitter : public AutoSplitterBase
//{
//private:
//    bool hasUpdatedOnce;
//    bool hasUpdatedTwice;
//
//    int previousRings;
//    int currentRings;
//
//    bool shouldStartTimer;
//    bool shouldSplitTimer;
//    bool shouldResetTimer;
//
//public:
//    explicit SpeedJumpRings1AutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);
//
//    bool update() override;
//    void onEvent(const std::string &eventName, bool post, void *params) override;
//
//    bool supportsStart() override;
//    bool supportsSplit() override;
//    bool supportsReset() override;
//
//    bool start() override;
//    bool split() override;
//    bool reset() override;
//
//    std::string getDebug() override;
//
//    std::string startDescription() override;
//    std::string splitDescription() override;
//    std::string resetDescription() override;
//};
