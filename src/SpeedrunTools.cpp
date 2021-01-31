#include "SpeedrunTools.h"
#include "toolkits/GeneralToolsToolkit.h"
#include "toolkits/SaveStatesToolkit.h"
#include "toolkits/LiveSplitToolkit.h"
#include "toolkits/KismetToolkit.h"
#include "toolkits/MapToolsToolkit.h"

BAKKESMOD_PLUGIN(SpeedrunTools, SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *SpeedrunTools::PLUGIN_VERSION = "2.1";
const char *SpeedrunTools::PLUGIN_TITLE = "Speedrun Tools";
const char *SpeedrunTools::PLUGIN_MENU_NAME = "speedruntools";

SpeedrunTools::SpeedrunTools()
        : BaseBakkesModPlugin(SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_MENU_NAME),
          toolkits()
{
    this->toolkits.push_back(std::make_unique<LiveSplitToolkit>(this));
    this->toolkits.push_back(std::make_unique<GeneralToolsToolkit>(this));
    this->toolkits.push_back(std::make_unique<SaveStatesToolkit>(this));
    this->toolkits.push_back(std::make_unique<KismetToolkit>(this));
    this->toolkits.push_back(std::make_unique<MapToolsToolkit>(this));
}

void SpeedrunTools::onLoad()
{
    this->setupEvents();
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
void SpeedrunTools::setupEvents()
{
    // tick (params for controller input override)
    this->gameWrapper->HookEventWithCaller<CarWrapper>(
            "Function TAGame.Car_TA.SetVehicleInput",
            [this](const CarWrapper &cw, void *params, const std::string &eventName) {
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, false, params);
                }
            }
    );
    this->setupEventPost("Function TAGame.Car_TA.SetVehicleInput");

    // map start end
    this->setupEventPost("Function TAGame.GameEvent_Soccar_TA.InitGame");
    this->setupEventPost("Function TAGame.GameEvent_Soccar_TA.Destroyed");

    // player resets
    this->setupEventPost("Function TAGame.GameEvent_TA.PlayerResetTraining");

    // tutorial only
    this->setupEventPost("Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay");
    this->setupEventPost("Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal");
    this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.Destroyed");

    // modal popup
    this->setupEventPost("Function TAGame.GFxShell_TA.ShowModalObject");
}

void SpeedrunTools::setupEvent(const std::string &eventName)
{
    this->gameWrapper->HookEvent(
            eventName,
            [this](const std::string &eventName) {
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, false, nullptr);
                }
            }
    );
}

void SpeedrunTools::setupEventPost(const std::string &eventName)
{
    this->gameWrapper->HookEventPost(
            eventName,
            [this](const std::string &eventName) {
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, true, nullptr);
                }
            }
    );
}
