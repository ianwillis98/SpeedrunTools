#pragma once

#include "../PluginToolkit.h"
#include "../../component/livesplit/LiveSplitComponent.h"
#include "../../component/livesplit/autosplitter/PanicsAirRaceBeachAutoSplitter.h"

class LiveSplitToolkit : public PluginToolkit
{
private:
    LiveSplitClient &liveSplitClient;

    LiveSplitComponent liveSplitComponent;
    PanicsAirRaceBeachAutoSplitter panicsAirRaceBeachAutoSplitter;

public:
    explicit LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void onConnect();
    void onDisconnect();

    void onStartOrSplit();

    void onStart();
    void onPause();
    void onResume();
    void onReset();

    void onSplit();
    void onSkipSplit();
    void onUndoSplit();

    void log(const std::string &message);
};
