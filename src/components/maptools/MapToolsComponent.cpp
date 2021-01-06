#include "MapToolsComponent.h"

MapToolsComponent::MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponentBase(plugin)
{

}

void MapToolsComponent::onLoad()
{
    // seg 4 ball locations, car loc = -0.004052 -5127.665039 150.564560
    // 2048 960 416
    // 1024 3008 512
    // 0 -1600 416
    // -1024 1472 512
    // -2048 -64 416
    this->plugin->cvarManager->registerNotifier("speedrun_tutorial_basic_practice_seg4", [this](const std::vector<std::string> &commands) {
        ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
        if (serverWrapper.IsNull()) return;

        this->plugin->gameWrapper->GetLocalCar().SetLocation(Vector(0.0f, -4859.0f, 17.01f));
        this->plugin->gameWrapper->GetLocalCar().SetRotation(Rotator(-100, 16384, 0));
        this->plugin->gameWrapper->GetLocalCar().SetVelocity(Vector(0.0f, 0.0f, 0.0f));
        this->plugin->gameWrapper->GetLocalCar().SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);

        std::vector<BallWrapper> ballsVector;
        auto ballsArrayWrapper = serverWrapper.GetGameBalls();
        for (const auto &ball : ballsArrayWrapper)
        {
            ballsVector.push_back(ball);
        }
        for (auto ball : ballsVector)
        {
            ball.DoDestroy();
        }

        serverWrapper.SpawnBall(Vector(2048.0f, 960.0f, 416.0f), true, false).Stop();
        serverWrapper.SpawnBall(Vector(1024.0f, 3008.0f, 512.0f), true, false).Stop();
        serverWrapper.SpawnBall(Vector(0.0f, -1600.0f, 416.0f), true, false).Stop();
        serverWrapper.SpawnBall(Vector(-1024.0f, 1472.0f, 512.0f), true, false).Stop();
        serverWrapper.SpawnBall(Vector(-2048.0f, -64.0f, 416.0f), true, false).Stop();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_tutorial_basic_practice_seg5", [this](const std::vector<std::string> &commands) {
        ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
        if (serverWrapper.IsNull()) return;

        this->plugin->gameWrapper->GetLocalCar().SetLocation(Vector(0.0f, -4859.0f, 17.01f));
        this->plugin->gameWrapper->GetLocalCar().SetRotation(Rotator(-100, 16384, 0));
        this->plugin->gameWrapper->GetLocalCar().SetVelocity(Vector(0.0f, 0.0f, 0.0f));
        this->plugin->gameWrapper->GetLocalCar().SetAngularVelocity(Vector(0.0f, 0.0f, 0.0f), false);

        std::vector<BallWrapper> ballsVector;
        auto ballsArrayWrapper = serverWrapper.GetGameBalls();
        for (const auto &ball : ballsArrayWrapper)
        {
            ballsVector.push_back(ball);
        }
        for (auto ball : ballsVector)
        {
            ball.DoDestroy();
        }

        serverWrapper.SpawnBall(Vector(2559.98999f, -3167.98999f, 864.0f), true, false).Stop();
        serverWrapper.SpawnBall(Vector(1919.98999f, 2720.01001f, 736.0f), true, false).Stop();
        serverWrapper.SpawnBall(Vector(-2432.01001f, 2720.01001f, 608.0f), true, false).Stop();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void MapToolsComponent::render()
{
    PluginComponentBase::render();
}

void MapToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
        if (serverWrapper.IsNull()) return;

        float x = serverWrapper.GetLocalPrimaryPlayer().GetLocation().X;
        float y = serverWrapper.GetLocalPrimaryPlayer().GetLocation().Y;
        float z = serverWrapper.GetLocalPrimaryPlayer().GetLocation().Z;
        //this->plugin->cvarManager->log("here12 " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));

//        auto balls = serverWrapper.GetGameBalls();
//
//        for (auto ball : balls)
//        {
//            float x = ball.GetLocation().X;
//            float y = ball.GetLocation().Y;
//            float z = ball.GetLocation().Z;
//            this->plugin->cvarManager->log("here11 " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
//        }
    }
}

// seg 4 ball locations, loc(0, -4859, 17.01) rot(-100, 16384, 0)
// 2048 960 416
// 1024 3008 512
// 0 -1600 416
// -1024 1472 512
// -2048 -64 416

// seg 5 ball locations, loc(0, -4859, 17.01) rot(-100, 16384, 0)
// 2559.98999 -3167.98999 864
// 1919.98999 2720.01001 736
// -2432.01001 2720.01001 608