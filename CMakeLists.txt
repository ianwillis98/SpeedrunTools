cmake_minimum_required(VERSION 3.16)
project(FreePlayTools)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(BAKKESMOD_PATH "[HKEY_CURRENT_USER\\Software\\BakkesMod\\AppPath;BakkesModPath]" ABSOLUTE)
#message("BAKKESMOD_PATH = ${BAKKESMOD_PATH}")

add_subdirectory(external/ocornut/imgui)
add_subdirectory(external/asio)

add_library(
        FreePlayTools SHARED
        src/FreePlayToolsPlugin.cpp src/FreePlayToolsPlugin.h
        src/plugin/BaseBakkesModPlugin.cpp src/plugin/BaseBakkesModPlugin.h
        src/toolkits/PluginToolkit.cpp src/toolkits/PluginToolkit.h
        src/toolkits/game/GameToolkit.cpp src/toolkits/game/GameToolkit.h
        src/toolkits/savestate/SaveStateToolkit.cpp src/toolkits/savestate/SaveStateToolkit.h
        src/models/CarState.cpp src/models/CarState.h
        src/models/BallState.cpp src/models/BallState.h
        src/services/MultiEventHooker.cpp src/services/MultiEventHooker.h
)

target_include_directories(
        FreePlayTools PRIVATE
        "${BAKKESMOD_PATH}/bakkesmodsdk/include"
        "external/ocornut/imgui"
        "external/asio"
)

target_link_libraries(
        FreePlayTools PRIVATE
        "${BAKKESMOD_PATH}/bakkesmodsdk/lib/pluginsdk.lib"
        ImGui
        asio
)

add_custom_command(
        TARGET FreePlayTools POST_BUILD
        COMMAND python tools/bakkes_patchplugin.py ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/FreePlayTools.dll
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running bakkes patch plugin..."
)
