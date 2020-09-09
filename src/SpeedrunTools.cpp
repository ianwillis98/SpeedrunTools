#include "SpeedrunTools.h"
#include "toolkit/mutators/MutatorsToolkit.h"
#include "toolkit/savestate/SaveStateToolkit.h"
#include "toolkit/analysis/AnalysisToolkit.h"
#include "toolkit/livesplit/LiveSplitToolkit.h"
#include "toolkit/kismet/KismetToolkit.h"
#include "toolkit/test/TestToolkit.h"

BAKKESMOD_PLUGIN(SpeedrunTools, SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *SpeedrunTools::PLUGIN_VERSION = "1.0";
const char *SpeedrunTools::PLUGIN_TITLE = "Speedrun Tools";
const char *SpeedrunTools::PLUGIN_MENU_NAME = "speedruntools";

SpeedrunTools::SpeedrunTools()
        : BaseBakkesModPlugin(SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_MENU_NAME), toolkits()
{
    this->toolkits.push_back(std::make_unique<MutatorsToolkit>(this));
    this->toolkits.push_back(std::make_unique<SaveStateToolkit>(this));
    this->toolkits.push_back(std::make_unique<AnalysisToolkit>(this));
    this->toolkits.push_back(std::make_unique<LiveSplitToolkit>(this));
    this->toolkits.push_back(std::make_unique<KismetToolkit>(this));

//    this->toolkits.push_back(std::make_unique<TestToolkit>(this));
}

void SpeedrunTools::onLoad()
{
    for (auto &toolkit : this->toolkits)
    {
        toolkit->onLoad();
    }
}

void SpeedrunTools::onUnload()
{
    for (auto &toolkit : this->toolkits)
    {
        toolkit->onUnload();
    }
}

void SpeedrunTools::renderBody()
{
//    static bool showDemoWindow = false;
//    ImGui::Checkbox("Show Demo Window", &showDemoWindow);
//    if (showDemoWindow)
//    {
//        ImGui::ShowDemoWindow();
//    }

    ImGui::Text("%s (version %s)", PLUGIN_TITLE, PLUGIN_VERSION);

    ImGui::Spacing();

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MainTabBar", tab_bar_flags))
    {
        for (auto &toolkit : this->toolkits)
        {
            if (ImGui::BeginTabItem(toolkit->title().c_str()))
            {
                toolkit->render();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}