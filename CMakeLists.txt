cmake_minimum_required(VERSION 3.17)
project(SpeedrunTools)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(BAKKESMOD_PATH "[HKEY_CURRENT_USER\\Software\\BakkesMod\\AppPath;BakkesModPath]" ABSOLUTE)
# message("BAKKESMOD_PATH = ${BAKKESMOD_PATH}")

add_subdirectory(external/ocornut/imgui)
add_subdirectory(external/asio)

add_library(
        SpeedrunTools SHARED
        src/SpeedrunTools.cpp src/SpeedrunTools.h
        src/plugin/BaseBakkesModPlugin.h src/plugin/BaseBakkesModPlugin.cpp
        src/toolkit/PluginToolkit.h src/toolkit/PluginToolkit.cpp
        src/component/PluginComponent.h src/component/PluginComponent.cpp
        src/toolkit/mutators/MutatorsToolkit.cpp src/toolkit/mutators/MutatorsToolkit.h
        src/component/game/GameGravityComponent.cpp src/component/game/GameGravityComponent.h
        src/utils/ImGuiExtensions.h src/utils/ImGuiExtensions.cpp
        src/component/game/GameSpeedComponent.cpp src/component/game/GameSpeedComponent.h
        src/component/car/AutoAirRollComponent.cpp src/component/car/AutoAirRollComponent.h
        src/component/car/BoostMutatorComponent.cpp src/component/car/BoostMutatorComponent.h
        src/services/MultiEventHooker.h src/services/MultiEventHooker.cpp
        src/models/CarState.h src/models/CarState.cpp
        src/models/BallState.h src/models/BallState.cpp
        src/models/GameState.h src/models/GameState.cpp
        src/component/savestate/RewindStateComponent.cpp src/component/savestate/RewindStateComponent.h
        src/component/savestate/RewindBuffer.h src/component/savestate/RewindBuffer.cpp
        src/toolkit/savestate/SaveStateToolkit.cpp src/toolkit/savestate/SaveStateToolkit.h
        src/component/savestate/SaveStateComponent.cpp src/component/savestate/SaveStateComponent.h
        src/toolkit/analysis/AnalysisToolkit.cpp src/toolkit/analysis/AnalysisToolkit.h
        src/component/car/CarAnalysisComponent.cpp src/component/car/CarAnalysisComponent.h
        src/component/ball/BallAnalysisComponent.cpp src/component/ball/BallAnalysisComponent.h
        src/toolkit/livesplit/LiveSplitToolkit.cpp src/toolkit/livesplit/LiveSplitToolkit.h
        src/component/livesplit/LiveSplitComponent.cpp src/component/livesplit/LiveSplitComponent.h
        src/services/LiveSplitClient.h src/services/LiveSplitClient.cpp src/component/kismet/SequenceVariableComponent.cpp src/component/kismet/SequenceVariableComponent.h src/toolkit/kismet/KismetToolkit.cpp src/toolkit/kismet/KismetToolkit.h src/toolkit/test/TestToolkit.cpp src/toolkit/test/TestToolkit.h src/models/KismetSequenceVariable.cpp src/models/KismetSequenceVariable.h)

target_include_directories(
        SpeedrunTools PRIVATE
        "${BAKKESMOD_PATH}/bakkesmodsdk/include"
        "external/ocornut/imgui"
        "external/asio"
)

target_link_libraries(
        SpeedrunTools PRIVATE
        "${BAKKESMOD_PATH}/bakkesmodsdk/lib/pluginsdk.lib"
        ImGui
        asio
)

set_property(TARGET SpeedrunTools PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)

add_custom_command(
        TARGET SpeedrunTools POST_BUILD
        COMMAND ${BAKKESMOD_PATH}/bakkesmodsdk/bakkesmod-patch.exe $<TARGET_FILE:SpeedrunTools>
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running bakkes patch plugin..."
)