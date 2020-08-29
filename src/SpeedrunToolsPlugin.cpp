#include "SpeedrunToolsPlugin.h"
#include "toolkit/game/GameToolkit.h"
#include "toolkit/savestate/SaveStateToolkit.h"
#include "toolkit/livesplit/LiveSplitToolkit.h"

BAKKESMOD_PLUGIN(SpeedrunToolsPlugin, SpeedrunToolsPlugin::PLUGIN_TITLE, SpeedrunToolsPlugin::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *SpeedrunToolsPlugin::PLUGIN_VERSION = "1.0";
const char *SpeedrunToolsPlugin::PLUGIN_TITLE = "Speedrun Tools";
const char *SpeedrunToolsPlugin::PLUGIN_MENU_NAME = "speedruntools";

SpeedrunToolsPlugin::SpeedrunToolsPlugin()
        : BaseBakkesModPlugin(SpeedrunToolsPlugin::PLUGIN_TITLE, SpeedrunToolsPlugin::PLUGIN_MENU_NAME), toolkits()
{
    this->toolkits.push_back(std::make_unique<GameToolkit>(this));
    this->toolkits.push_back(std::make_unique<SaveStateToolkit>(this));
    this->toolkits.push_back(std::make_unique<LiveSplitToolkit>(this));
}

void SpeedrunToolsPlugin::onLoad()
{
    for (auto &toolkit : this->toolkits)
    {
        toolkit->onLoad();
    }
}

void SpeedrunToolsPlugin::onUnload()
{
    for (auto &toolkit : this->toolkits)
    {
        toolkit->onUnload();
    }
}

void SpeedrunToolsPlugin::RenderBody()
{
    static bool showDemoWindow = false;
    ImGui::Checkbox("Show Demo Window", &showDemoWindow);
    if (showDemoWindow)
    {
        ImGui::ShowDemoWindow();
    }

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