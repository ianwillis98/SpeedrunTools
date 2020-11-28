#pragma once

#include <bakkesmod/wrappers/wrapperstructs.h>
#include <bakkesmod/wrappers/GameObject/CarWrapper.h>
#include <bakkesmod/wrappers/GameObject/CarComponent/BoostWrapper.h>

class CarState
{
public:
    Vector position;
    Rotator rotation;
    Vector velocity;
    Vector angularVelocity;
    float boostAmount;

    CarState();
    explicit CarState(CarWrapper &car);

    void applyTo(CarWrapper &car) const;
    void render();
};
