#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "../PluginToolkit.h"
#include "../../services/LiveSplitClient.h"

class LiveSplitToolkit : public PluginToolkit
{
private:
    LiveSplitClient &liveSplitClient;

public:
    explicit LiveSplitToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    void connect();

    void startOrSplit();

    void start();
    void pause();
    void resume();
    void reset();

    void split();
    void skipSplit();
    void undoSplit();
};
