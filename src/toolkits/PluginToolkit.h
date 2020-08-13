#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <imgui.h>
#include <imgui_internal.h>

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
