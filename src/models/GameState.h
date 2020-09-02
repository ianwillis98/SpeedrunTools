#pragma once

#include <bakkesmod/wrappers/GameEvent/ServerWrapper.h>
#include "CarState.h"
#include "BallState.h"

class GameState
{
public:
    GameState();

    explicit GameState(ServerWrapper &server);

    void applyTo(ServerWrapper &server) const;

    void render();

public:
    CarState carState;
    BallState ballState;
};
