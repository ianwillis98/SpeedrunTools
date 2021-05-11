#pragma once

#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/GameObject/CarWrapper.h>
#include <bakkesmod/wrappers/GameObject/CarComponent/BoostWrapper.h>

class CarState
{
public:
    Vector location;
    Rotator rotation;
    Vector velocity;
    Vector angularVelocity;
    float boostAmount;

    explicit CarState(CarWrapper &car);
    explicit CarState(Vector location = Vector(0.0f, 0.0f, 0.0f),
                      Rotator rotation = Rotator(0, 0, 0),
                      Vector velocity = Vector(0.0f, 0.0f, 0.0f),
                      Vector angularVelocity = Vector(0.0f, 0.0f, 0.0f),
                      float boostAmount = 0.0f);

    void applyTo(CarWrapper &car) const;
    bool render();
};
