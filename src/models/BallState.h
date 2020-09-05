#pragma once

#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/GameObject/BallWrapper.h>

class BallState
{
public:
    Vector position;
    Rotator rotation;
    Vector velocity;
    Vector angularVelocity;

    BallState();
    explicit BallState(BallWrapper &ball);

    void applyTo(BallWrapper &ball) const;

    void render();
};
