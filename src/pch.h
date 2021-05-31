#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceOpWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceObjectWrapper.h>
#include <bakkesmod/wrappers/Engine/UnrealStringWrapper.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "utils/ImGuiExtensions.h"
#include "utils/CVarFunctions.h"
