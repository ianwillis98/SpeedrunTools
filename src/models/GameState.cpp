#include <imgui.h>
#include "GameState.h"

GameState::GameState() = default;

GameState::GameState(ServerWrapper &server)
{
    if (server.IsNull()) return;

    CarWrapper car = server.GetGameCar();
    carState = CarState(car);

    BallWrapper ball = server.GetBall();
    ballState = BallState(ball);
}

void GameState::applyTo(ServerWrapper &server) const
{
    if (server.IsNull()) return;

    CarWrapper carWrapper = server.GetGameCar();
    carState.applyTo(carWrapper);

    BallWrapper ballWrapper = server.GetBall();
    ballState.applyTo(ballWrapper);
}

bool GameState::render()
{
    bool hasChanged = false;

    ImGui::Text("Saved car state:");
    if (this->carState.render()) hasChanged = true;
    ImGui::Separator();
    ImGui::Text("Saved ball state:");
    if (this->ballState.render()) hasChanged = true;

    return hasChanged;
}
