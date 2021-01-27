#pragma once

#include "../AutoSplitterBase.h"

class AirDribbleHoopsAutoSplitter : public AutoSplitterBase
{
private:
    bool hasUpdatedOnce;
    bool hasUpdatedTwice;

    bool currentTimer;
    bool previousTimer;

    int currentLevel;
    int previousLevel;

public:
    explicit AirDribbleHoopsAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEventReceived(const std::string &eventName, bool post, void *params) override;

    bool supportsReset() override;

    std::string startDescription() override;
    std::string splitDescription() override;
    std::string resetDescription() override;

    std::string getDebug() override;
};
