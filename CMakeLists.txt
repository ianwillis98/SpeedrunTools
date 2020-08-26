cmake_minimum_required(VERSION 3.16)
project(SpeedrunTools)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(BAKKESMOD_PATH "[HKEY_CURRENT_USER\\Software\\BakkesMod\\AppPath;BakkesModPath]" ABSOLUTE)
#message("BAKKESMOD_PATH = ${BAKKESMOD_PATH}")

add_subdirectory(external/ocornut/imgui)
add_subdirectory(external/asio)

add_library(
        SpeedrunTools SHARED
        src/SpeedrunTools.cpp src/SpeedrunTools.h
        src/plugin/BaseBakkesModPlugin.cpp src/plugin/BaseBakkesModPlugin.h
        src/toolkits/PluginToolkit.cpp src/toolkits/PluginToolkit.h
        src/toolkits/game/GameToolkit.cpp src/toolkits/game/GameToolkit.h
        src/toolkits/savestate/SaveStateToolkit.cpp src/toolkits/savestate/SaveStateToolkit.h
        src/models/CarState.cpp src/models/CarState.h
        src/models/BallState.cpp src/models/BallState.h
        src/services/MultiEventHooker.cpp src/services/MultiEventHooker.h
        src/toolkits/test/TestToolkit.cpp src/toolkits/test/TestToolkit.h
        src/toolkits/savestate/SaveState.cpp src/toolkits/savestate/SaveState.h
        src/toolkits/savestate/SaveStateBuffer.cpp src/toolkits/savestate/SaveStateBuffer.h
        src/services/LiveSplitClient.cpp src/services/LiveSplitClient.h
        src/toolkits/livesplit/LiveSplitToolkit.cpp src/toolkits/livesplit/LiveSplitToolkit.h)

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
