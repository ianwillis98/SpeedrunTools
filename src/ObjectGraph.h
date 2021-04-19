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
#include "utils/CVarFunctions.h"

#include "PluginController.h"
#include "livesplit/LiveSplitModel.h"
#include "livesplit/LiveSplitController.h"

class ObjectGraph
{
public:
    explicit ObjectGraph(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    std::vector<std::shared_ptr<PluginModel>> models;
    std::vector<std::pair<std::string, std::shared_ptr<PluginController>>> tabs;

    // models
    std::shared_ptr<LiveSplitModel> liveSplitModel;

    // controllers
    std::shared_ptr<LiveSplitController> liveSplitController;
};
