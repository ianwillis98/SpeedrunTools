#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>

class PluginToolkit
{
public:
    explicit PluginToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    virtual std::string title() = 0;
    virtual void onLoad() = 0;
    virtual void onUnload() = 0;
    virtual void render() = 0;

protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;
};
