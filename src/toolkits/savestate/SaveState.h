#pragma once

#include <bakkesmod/wrappers/GameEvent/ServerWrapper.h>
#include "../../models/CarState.h"
#include "../../models/BallState.h"


class SaveState
{
public:
    SaveState();
    explicit SaveState(ServerWrapper &serverWrapper);

    void applyTo(ServerWrapper &serverWrapper);

    void render(const std::string &tag);

public:
    CarState carState;
    BallState ballState;
};
