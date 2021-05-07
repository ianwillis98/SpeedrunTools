#include "TutorialAdvancedComponent.h"

TutorialAdvancedComponent::TutorialAdvancedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginComponentBase(plugin)
{
    this->plugin->cvarManager->registerNotifier("speedrun_tutorial_advanced_practice_seg4", [this](const std::vector<std::string> &commands) {
        this->practiceSeg4();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_tutorial_advanced_practice_seg5", [this](const std::vector<std::string> &commands) {
        this->practiceSeg5();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void TutorialAdvancedComponent::render()
{
    ImGui::Text("Tutorial Advanced Map Tools");
    ImGuiExtensions::BigSpacing();

    if (ImGui::Button("Practice Segment 4"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSeg4();
        });
    }
    ImGui::Spacing();

    if (ImGui::Button("Practice Segment 5"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSeg5();
        });
    }
}

void TutorialAdvancedComponent::practiceSeg4()
{
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
}

void TutorialAdvancedComponent::practiceSeg5()
{
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
}
