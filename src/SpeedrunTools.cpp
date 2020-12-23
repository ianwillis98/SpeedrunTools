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
            [this](CarWrapper cw, void *params, const std::string &eventName) {
                std::string x = std::to_string(cw.GetLocation().X);
                std::string y = std::to_string(cw.GetLocation().Y);
                std::string z = std::to_string(cw.GetLocation().Z);
                std::string a = std::to_string(cw.GetRotation().Yaw);
                std::string b = std::to_string(cw.GetRotation().Pitch);
                std::string c = std::to_string(cw.GetRotation().Roll);
                //this->cvarManager->log(x + " " + y + " " + z + " " + a + " " + b + " " + c);
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, false, params);
                }
            }
    );
    this->setupEventPostDelayed("Function TAGame.GameEvent_Soccar_TA.InitGame", 0.2f);
    this->setupEventPost("Function TAGame.GameEvent_Soccar_TA.Destroyed");

    // tutorial
    this->setupEventPostDelayed("Function TAGame.GameInfo_Tutorial_TA.PostBeginPlay", 0.2f);
    this->setupEventPost("Function GameEvent_Tutorial_Basic_TA.Active.HandleHitGoal");
    this->setupEventPost("Function TAGame.GFxShell_TA.ShowModalObject");
    this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.Destroyed");

//    this->setupEventPost("Function TAGame.GameEvent_Tutorial_FreePlay_TA.InitMutators");
//    this->setupEventPost("Function TAGame.GameEvent_Tutorial_Basic_TA.GetTotalRounds");
//    this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.OnInit");

//    this->setupEventPost("Function TAGame.GFxShell_TA.OnShowModal");

//    this->setupEventPost("Function TAGame.SeqAct_EndTutorial_TA.Activated");
//    this->setupEventPost("Function GameEvent_Tutorial_TA.Active.BeginState");
//    this->setupEventPost("Function GameEvent_Tutorial_TA.Active.EndState");
//    this->setupEventPost("Function TAGame.GFxShell_TA.OnShowModal");
//    this->setupEventPost("Function TAGame.GFxShell_TA.ShowModalObject");
    //this->setupEventPost("Function AkAudio.AkMusicDevice.Play");
    //this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.HandleTutorialComplete");
    //this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.StartTutorial");
    //this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.EndTutorial");
    //this->setupEventPost("Function TAGame.GameEvent_Tutorial_TA.Destroyed");
    //this->setupEventPost("Function AkAudio.AkDevice.GetEnvironments");
    //this->setupEventPost("Function AkAudio.AkDevice.PlaySound");
    //this->setupEventPost("Function AkAudio.AkDevice.StopSound");
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
    static int count = 0;
    this->gameWrapper->HookEventPost(
            eventName,
            [this](const std::string &eventName) {
                std::string map = this->gameWrapper->GetCurrentMap();
                this->cvarManager->log(std::to_string(count++) + " " + map + " " + eventName);
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, true, nullptr);
                }
            }
    );
}

void SpeedrunTools::setupEventPostDelayed(const std::string &eventName, float delay)
{
    static int count = 0;
    this->gameWrapper->HookEventPost(
            eventName,
            [this](const std::string &eventName) {
                std::string map = this->gameWrapper->GetCurrentMap();
                this->cvarManager->log(std::to_string(count++) + " " + map + " " + eventName);
                for (auto &toolkit : this->toolkits)
                {
                    toolkit->onEvent(eventName, true, nullptr);
                }
                this->gameWrapper->SetTimeout([this, eventName](GameWrapper *gw) {
                    std::string map = this->gameWrapper->GetCurrentMap();
                    this->cvarManager->log(std::to_string(count++) + " " + map + " " + eventName + " Delayed");
                    for (auto &toolkit : this->toolkits)
                    {
                        toolkit->onEvent(eventName + " Delayed", true, nullptr);
                    }
                }, 0.2f);
            }
    );
}
