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
public:
    virtual void onLoad() = 0;
    virtual void onUnload() = 0;
    virtual void render() = 0;
    virtual void onEvent(const std::string &eventName, bool post, void *params) = 0;
};