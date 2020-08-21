//
// Created by Ian on 8/15/2020.
//

#include "TestToolkit.h"

TestToolkit::TestToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{

}

std::string TestToolkit::title()
{
    return "Test Toolkit";
}

void TestToolkit::onLoad()
{
    this->plugin->cvarManager->registerNotifier("st_test", [this](const std::vector<std::string> &commands) {
        ServerWrapper s = this->plugin->gameWrapper->GetGameEventAsServer();
        this->plugin->gameWrapper->LogToChatbox("before " + std::to_string(s.GetGameSpeed()));
        s.SetGameSpeed(3.0f);
        this->plugin->gameWrapper->LogToChatbox("after " + std::to_string(s.GetGameSpeed()));
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_test2", [this](const std::vector<std::string> &commands) {
        ServerWrapper s = this->plugin->gameWrapper->GetGameEventAsServer();
        this->plugin->gameWrapper->LogToChatbox("after " + std::to_string(s.GetGameSpeed()));
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    //this->plugin->gameWrapper->GetGameEventAsServer().SetGameSpeed(3.0f);
}

void TestToolkit::onUnload()
{

}

void TestToolkit::render()
{

}
