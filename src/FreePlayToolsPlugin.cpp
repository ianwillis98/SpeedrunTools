#include "FreePlayToolsPlugin.h"
#include "toolkits/game/GameToolkit.h"
#include "toolkits/savestate/SaveStateToolkit.h"
#include "toolkits/test/TestToolkit.h"

BAKKESMOD_PLUGIN(FreePlayToolsPlugin, FreePlayToolsPlugin::PLUGIN_TITLE,
                 FreePlayToolsPlugin::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *FreePlayToolsPlugin::PLUGIN_VERSION = "1.0";
const char *FreePlayToolsPlugin::PLUGIN_TITLE = "Free Play Tools";
const char *FreePlayToolsPlugin::PLUGIN_MENU_NAME = "freeplaytools";

FreePlayToolsPlugin::FreePlayToolsPlugin() : BaseBakkesModPlugin(FreePlayToolsPlugin::PLUGIN_TITLE,
                                                                 FreePlayToolsPlugin::PLUGIN_MENU_NAME)
{
    this->toolkits.push_back(std::make_unique<GameToolkit>(this));
    this->toolkits.push_back(std::make_unique<SaveStateToolkit>(this));
    this->toolkits.push_back(std::make_unique<TestToolkit>(this));
}

void FreePlayToolsPlugin::onLoad()
{
    for (auto &toolkit : this->toolkits)
    {
        toolkit->onLoad();
    }
}

void FreePlayToolsPlugin::onUnload()
{
    for (auto &toolkit : this->toolkits)
    {
        toolkit->onUnload();
    }
}

void FreePlayToolsPlugin::RenderBody()
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