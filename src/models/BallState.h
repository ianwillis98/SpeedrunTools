#pragma once

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
    bool render();
};
