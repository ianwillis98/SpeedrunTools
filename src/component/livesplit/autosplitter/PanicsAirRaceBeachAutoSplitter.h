#pragma once

#include <map>
#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include "../../PluginComponent.h"
#include "../../../services/LiveSplitClient.h"

class PanicsAirRaceBeachAutoSplitter : public PluginComponent
{
private:
    LiveSplitClient &liveSplitClient;
    bool isAutoSplitterRunning;

    std::vector<int> gateSplits;
    std::vector<int> checkpointSplits;
    int previousCount;
    int previousCpCount;

public:
    explicit PanicsAirRaceBeachAutoSplitter(BakkesMod::Plugin::BakkesModPlugin *plugin, LiveSplitClient &liveSplitClient);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    void startAutoSplitter();
    void stopAutoSplitter();

private:
    void onPhysicsTick();
};
