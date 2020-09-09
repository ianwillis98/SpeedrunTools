#include "TestToolkit.h"
#include "../../services/MultiEventHooker.h"

TestToolkit::TestToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{

}

std::string TestToolkit::title()
{
    return "Testing";
}

void TestToolkit::onLoad()
{
    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &event) {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (server.IsNull()) return;

        BallWrapper ball = server.GetBall();
        if (ball.IsNull()) return;

        server.DestroyBalls();
    });
}

void TestToolkit::onUnload()
{

}

void TestToolkit::render()
{

}
