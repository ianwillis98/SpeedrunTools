#include <imgui.h>
#include "GameState.h"

GameState::GameState() = default;

GameState::GameState(ServerWrapper &serverWrapper)
{
    if (serverWrapper.IsNull()) return;

    CarWrapper carWrapper = serverWrapper.GetGameCar();
    if (!carWrapper.IsNull())
    {
        carState = CarState(carWrapper);
    }

    BallWrapper ballWrapper = serverWrapper.GetBall();
    if (!ballWrapper.IsNull())
    {
        ballState = BallState(ballWrapper);
    }
}

void GameState::applyTo(ServerWrapper &serverWrapper) const
{
    if (serverWrapper.IsNull()) return;

    CarWrapper carWrapper = serverWrapper.GetGameCar();
    if (!carWrapper.IsNull())
    {
        carState.applyTo(carWrapper);
    }

    BallWrapper ballWrapper = serverWrapper.GetBall();
    if (!ballWrapper.IsNull())
    {
        ballState.applyTo(ballWrapper);
    }
}

void GameState::render(const std::string &tag)
{
    this->carState.render(tag + " car");
    ImGui::Spacing();
    this->ballState.render(tag + " ball");
}
