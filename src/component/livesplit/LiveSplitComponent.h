#pragma once

#include "../PluginComponent.h"
#include "../../services/LiveSplitClient.h"

class LiveSplitComponent : public PluginComponent
{
private:
    LiveSplitClient &liveSplitClient;

public:
    explicit LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    void connectAsync();
    void disconnect();

    void startOrSplit();

    void start();
    void pause();
    void resume();
    void reset();

    void split();
    void skipSplit();
    void undoSplit();
};
