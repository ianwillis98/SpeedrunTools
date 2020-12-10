#pragma once

#include <sstream>
#include <map>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include "../PluginComponent.h"
#include "../models/KismetSequenceVariable.h"
#include "../services/LiveSplitClient.h"

class TestComponent : public PluginComponent
{
private:
    LiveSplitClient &liveSplitClient;
    bool running;
    int previousLevel;
    bool previousTiming;

public:
    explicit TestComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(std::string eventName, bool post, void *params) override;

    void changeLevel();
};
