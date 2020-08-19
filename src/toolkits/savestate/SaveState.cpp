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

void SaveState::applyTo(ServerWrapper &serverWrapper)
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
