#include "SpeedrunTools.h"
#include "toolkits/livesplit/LiveSplitToolkit.h"


BAKKESMOD_PLUGIN(SpeedrunTools, SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_VERSION, PLUGINTYPE_CUSTOM_TRAINING)

const char *SpeedrunTools::PLUGIN_VERSION = "1.0";
const char *SpeedrunTools::PLUGIN_TITLE = "Speedrun Tools";
const char *SpeedrunTools::PLUGIN_MENU_NAME = "speedruntools";

SpeedrunTools::SpeedrunTools()
        : BaseBakkesModPlugin(SpeedrunTools::PLUGIN_TITLE, SpeedrunTools::PLUGIN_MENU_NAME),
          toolkits()
{
    this->toolkits.push_back(std::make_unique<LiveSplitToolkit>(this));
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
void SpeedrunTools::setupEvents()
{
    this->gameWrapper->HookEventWithCaller<CarWrapper>(
            "Function TAGame.Car_TA.SetVehicleInput",
            [this](const CarWrapper &cw, void *params, const std::string &eventName) {
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, false, params);
                }
            }
    );
    this->setupEventPostDelayed("Function TAGame.GameEvent_Soccar_TA.InitGame", 0.2f);
    this->setupEventPost("Function TAGame.GameEvent_Soccar_TA.Destroyed");

    this->setupEventPostDelayed("Function TAGame.GameEvent_Tutorial_TA.OnInit", 0.2f);
    this->setupEventPost("Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal");
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
                    toolkit->onEvent(eventName, false, nullptr);
                }
            }
    );
}

void SpeedrunTools::setupEventPostDelayed(const std::string &eventName, float delay)
{
    this->gameWrapper->HookEventPost(
            eventName,
            [this](const std::string &eventName) {
                this->gameWrapper->SetTimeout([this, eventName](GameWrapper *gw) {
                    for (auto &toolkit : this->toolkits)
                    {
                        toolkit->onEvent(eventName + " Delayed", true, nullptr);
                    }
                }, 0.2f);
            }
    );
}
