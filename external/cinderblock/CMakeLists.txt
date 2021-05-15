file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "renderingtools/*.h" "renderingtools/*.cpp")
add_library(RenderingTools ${SOURCE_FILES})

get_filename_component(BAKKESMOD_PATH "[HKEY_CURRENT_USER\\Software\\BakkesMod\\AppPath;BakkesModPath]" ABSOLUTE)

target_include_directories(
        RenderingTools PRIVATE
        "${BAKKESMOD_PATH}/bakkesmodsdk/include"
)

target_link_libraries(
        RenderingTools PRIVATE
        "${BAKKESMOD_PATH}/bakkesmodsdk/lib/pluginsdk.lib"
)

set_property(TARGET RenderingTools PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)