#pragma once

#include "../PluginToolkit.h"

class PluginToolkitBase : public PluginToolkit
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

public:
    explicit PluginToolkitBase(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void * params) override;
};
