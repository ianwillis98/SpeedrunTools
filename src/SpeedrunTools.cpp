#include "SpeedrunTools.h"
#include "components/MutatorsComponent.h"
#include "components/SaveStatesComponent.h"
#include "components/LiveSplitComponent.h"
#include "components/KismetComponent.h"

BAKKESMOD_PLUGIN(SpeedrunTools, SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *SpeedrunTools::PLUGIN_VERSION = "1.0";
const char *SpeedrunTools::PLUGIN_TITLE = "Speedrun Tools";
const char *SpeedrunTools::PLUGIN_MENU_NAME = "speedruntools";

SpeedrunTools::SpeedrunTools()
        : BaseBakkesModPlugin(SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_MENU_NAME), components()
{
    this->components.push_back(std::make_unique<MutatorsComponent>(this));
    this->components.push_back(std::make_unique<SaveStatesComponent>(this));
    this->components.push_back(std::make_unique<LiveSplitComponent>(this));
    this->components.push_back(std::make_unique<KismetComponent>(this));
}

void SpeedrunTools::onLoad()
{
    this->setupEvents();
    for (auto &component : this->components)
    {
        component->onLoad();
    }
}

void SpeedrunTools::onUnload()
{
    for (auto &component : this->components)
    {
        component->onUnload();
    }
}

void SpeedrunTools::renderBody()
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
        for (auto &component : this->components)
        {
            if (ImGui::BeginTabItem(component->title().c_str()))
            {
                component->render();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}
void SpeedrunTools::setupEvents()
{
    this->gameWrapper->HookEventWithCaller<CarWrapper>(
            "Function TAGame.Car_TA.SetVehicleInput",
            [this](const CarWrapper &cw, void *params, const std::string &eventName) {
                for (auto &component : this->components)
                {
                    component->onEvent(eventName, false, params);
                }
            }
    );
}
