#include "BallState.h"

BallState::BallState(BallWrapper &ball)
{
    if (ball.IsNull()) return;

    this->position = ball.GetLocation();
    this->rotation = ball.GetRotation();
    this->velocity = ball.GetVelocity();
    this->angularVelocity = ball.GetAngularVelocity();
}

BallState::BallState(Vector position, Rotator rotation, Vector velocity, Vector angularVelocity)
{
    this->position = position;
    this->rotation = rotation;
    this->velocity = velocity;
    this->angularVelocity = angularVelocity;
}

void BallState::applyTo(BallWrapper &ball) const
{
    if (ball.IsNull()) return;

    ball.SetLocation(this->position);
    ball.SetRotation(this->rotation);
    ball.SetVelocity(this->velocity);
    ball.SetAngularVelocity(this->angularVelocity, false);
}