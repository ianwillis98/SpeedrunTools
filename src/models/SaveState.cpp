#include <imgui.h>
#include "SaveState.h"

SaveState::SaveState() = default;

SaveState::SaveState(ServerWrapper &serverWrapper)
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

void SaveState::applyTo(ServerWrapper &serverWrapper) const
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

void SaveState::render(const std::string &tag)
{
    this->carState.render(tag + " car");
    ImGui::Spacing();
    this->ballState.render(tag + " ball");
}
