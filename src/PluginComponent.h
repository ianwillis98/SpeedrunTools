#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/plugin/pluginwindow.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "utils/ImGuiExtensions.h"

class PluginComponent
{
protected:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

public:
    explicit PluginComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
    {}

    virtual std::string title()
    {
        return "";
    }

    virtual void onLoad()
    {}

    virtual void onUnload()
    {}

    virtual void render()
    {}

    virtual void onEvent(std::string eventName, bool post, void *params)
    {}
};