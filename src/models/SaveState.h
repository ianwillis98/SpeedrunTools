#pragma once

#include <bakkesmod/wrappers/GameEvent/ServerWrapper.h>
#include "CarState.h"
#include "BallState.h"

class SaveState
{
public:
    SaveState();

    explicit SaveState(ServerWrapper &serverWrapper);

    void applyTo(ServerWrapper &serverWrapper) const;

    void render(const std::string &tag);

public:
    CarState carState;
    BallState ballState;
};
