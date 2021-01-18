cmake_minimum_required(VERSION 3.17)
project(SpeedrunTools)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(BAKKESMOD_PATH "[HKEY_CURRENT_USER\\Software\\BakkesMod\\AppPath;BakkesModPath]" ABSOLUTE)
message("BAKKESMOD_PATH = ${BAKKESMOD_PATH}")

add_subdirectory(external/ocornut/imgui)
add_subdirectory(external/asio)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
add_library(SpeedrunTools SHARED ${SOURCE_FILES} src/components/livesplit/autosplitters/runs/PanicsAirRaceBeachAutoSplitter.cpp src/components/livesplit/autosplitters/runs/PanicsAirRaceBeachAutoSplitter.h src/components/kismet/KismetEditorComponent.cpp src/components/kismet/KismetEditorComponent.h src/toolkits/GeneralToolsToolkit.cpp src/toolkits/GeneralToolsToolkit.h src/components/generaltools/GeneralToolsComponent.cpp src/components/generaltools/GeneralToolsComponent.h src/toolkits/SaveStatesToolkit.cpp src/toolkits/SaveStatesToolkit.h src/components/savestates/SaveStateComponent.cpp src/components/savestates/SaveStateComponent.h src/components/savestates/RewindComponent.cpp src/components/savestates/RewindComponent.h)

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

target_link_options(SpeedrunTools PUBLIC "/DEBUG")
set_target_properties(SpeedrunTools PROPERTIES COMPILE_OPTIONS "/Zi")
set_target_properties(
        SpeedrunTools PROPERTIES
        COMPILE_PDB_NAME "SpeedrunTools"
        COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_property(TARGET SpeedrunTools PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)

add_custom_command(
        TARGET SpeedrunTools POST_BUILD
        COMMAND ${BAKKESMOD_PATH}/bakkesmodsdk/bakkesmod-patch.exe $<TARGET_FILE:SpeedrunTools>
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running bakkes patch plugin..."
)