#pragma once

#include "../../models/CarState.h"
#include "../../models/BallState.h"
#include <bakkesmod/wrappers/GameEvent/ServerWrapper.h>


class SaveState
{
public:
    explicit SaveState(ServerWrapper &serverWrapper);
    SaveState(CarState carState, BallState ballState);
    SaveState();

    void applyTo(ServerWrapper &serverWrapper);

private:
    CarState carState;
    BallState ballState;
};
