cmake_minimum_required(VERSION 3.17)
project(SpeedrunTools)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(BAKKESMOD_PATH "[HKEY_CURRENT_USER\\Software\\BakkesMod\\AppPath;BakkesModPath]" ABSOLUTE)
#message("BAKKESMOD_PATH = ${BAKKESMOD_PATH}")

add_subdirectory(external/ocornut/imgui)
add_subdirectory(external/asio)

add_library(
        SpeedrunTools SHARED
        src/plugin/BaseBakkesModPlugin.cpp src/plugin/BaseBakkesModPlugin.h
        src/SpeedrunToolsPlugin.cpp src/SpeedrunToolsPlugin.h
        src/toolkit/mutators/MutatorsToolkit.cpp src/toolkit/mutators/MutatorsToolkit.h
        src/components/game/GameGravityComponent.cpp src/components/game/GameGravityComponent.h
        src/plugin/PluginComponent.cpp src/plugin/PluginComponent.h
        src/components/game/GameSpeedComponent.cpp src/components/game/GameSpeedComponent.h
        src/toolkit/PluginToolkit.cpp src/toolkit/PluginToolkit.h
        src/components/savestate/SaveStateComponent.cpp src/components/savestate/SaveStateComponent.h
        src/components/savestate/RewindStateComponent.cpp src/components/savestate/RewindStateComponent.h
        src/models/CarState.h src/models/CarState.cpp
        src/models/BallState.h src/models/BallState.cpp
        src/models/GameState.h src/models/GameState.cpp
        src/services/MultiEventHooker.h src/services/MultiEventHooker.cpp
        src/utils/ImGuiExtensions.cpp src/utils/ImGuiExtensions.h
        src/toolkit/savestate/SaveStateToolkit.cpp src/toolkit/savestate/SaveStateToolkit.h
        src/components/savestate/RewindBuffer.h src/components/savestate/RewindBuffer.cpp
        src/components/livesplit/LiveSplitComponent.cpp src/components/livesplit/LiveSplitComponent.h
        src/toolkit/livesplit/LiveSplitToolkit.cpp src/toolkit/livesplit/LiveSplitToolkit.h
        src/services/LiveSplitClient.h src/services/LiveSplitClient.cpp
        src/components/car/AutoAirRollComponent.cpp src/components/car/AutoAirRollComponent.h)

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

add_custom_command(
        TARGET SpeedrunTools POST_BUILD
        COMMAND python tools/bakkes_patchplugin.py $<TARGET_FILE:SpeedrunTools>
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running bakkes patch plugin..."
)