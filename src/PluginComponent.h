#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <map>
#include <sstream>
#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/plugin/pluginwindow.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "utils/ImGuiExtensions.h"
#include "utils/HelperFunctions.h"

class PluginComponent
{
public:
    virtual void onLoad() = 0;
    virtual void onUnload() = 0;
    virtual void render() = 0;
    virtual void onEvent(const std::string &eventName, bool post, void *params) = 0;
};