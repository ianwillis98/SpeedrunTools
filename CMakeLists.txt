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
        src/toolkit/game/GameToolkit.cpp src/toolkit/game/GameToolkit.h
        src/components/game/GameGravityComponent.cpp src/components/game/GameGravityComponent.h src/plugin/PluginComponent.cpp src/plugin/PluginComponent.h src/components/game/GameSpeedComponent.cpp src/components/game/GameSpeedComponent.h src/toolkit/PluginToolkit.cpp src/toolkit/PluginToolkit.h)

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