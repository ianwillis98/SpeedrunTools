#include "SpeedrunTools.h"
#include "components/generaltools/GeneralToolsComponent.h"
#include "components/livesplit/LiveSplitComponent.h"
#include "components/kismet/KismetEditorComponent.h"
#include "components/savestates/SaveStateComponent.h"
#include "components/maptools/MapToolsComponent.h"

BAKKESMOD_PLUGIN(SpeedrunTools, SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *SpeedrunTools::PLUGIN_VERSION = "3.0";
const char *SpeedrunTools::PLUGIN_TITLE = "Speedrun Tools";
const char *SpeedrunTools::PLUGIN_MENU_NAME = "speedruntools";

SpeedrunTools::SpeedrunTools()
        : BaseBakkesModPlugin(SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_MENU_NAME),
          objects(this)
{

}

void SpeedrunTools::onLoad()
{
    this->setupEvents();
    for (auto &tab : this->objects.tabs)
    {
        tab.second->onLoad();
    }
}

void SpeedrunTools::onUnload()
{
    for (auto &tab : this->objects.tabs)
    {
        tab.second->onUnload();
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

    if (ImGui::BeginTabBar("MainTabBar", ImGuiTabBarFlags_None))
    {
        for (auto &tab : this->objects.tabs)
        {
            if (ImGui::BeginTabItem(tab.first.c_str()))
            {
                tab.second->render();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}
void SpeedrunTools::setupEvents()
{
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
                for (auto &model : this->objects.models) model->onEvent(eventName, false, nullptr);
            }
    );
}

void SpeedrunTools::setupEventPost(const std::string &eventName)
{
    this->gameWrapper->HookEventPost(
            eventName,
            [this](const std::string &eventName) {
                for (auto &model : this->objects.models) model->onEvent(eventName, true, nullptr);
            }
    );
}
