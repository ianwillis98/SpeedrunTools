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

void GameState::render()
{
    ImGui::Text("Saved car state:");
    this->carState.render();
    ImGui::Spacing();
    ImGui::Text("Saved ball state:");
    this->ballState.render();
}
