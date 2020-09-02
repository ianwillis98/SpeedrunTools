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

    explicit BallState(BallWrapper &ball);
    explicit BallState(
            Vector position = Vector(0, 0, 0),
            Rotator rotation = Rotator(0, 0, 0),
            Vector velocity = Vector(0, 0, 0),
            Vector angularVelocity = Vector(0, 0, 0)
    );

    void applyTo(BallWrapper &ball) const;

    void render();
};
