#pragma once

#include "../PluginView.h"

class LiveSplitConnectView : public PluginView
{
private:
    std::function<void()> onConnectionButtonClickCallback;
    bool connecting;

public:
    explicit LiveSplitConnectView(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;

    void setOnConnectButtonClickCallback(std::function<void()> callback);
    void setConnecting(bool c);
};
