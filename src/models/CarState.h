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

    explicit CarState(CarWrapper &car);
    explicit CarState(
            Vector position = Vector(0, 0, 0),
            Rotator rotation = Rotator(0, 0, 0),
            Vector velocity = Vector(0, 0, 0),
            Vector angularVelocity = Vector(0, 0, 0),
            float boostAmount = 0.0f
    );

    void applyTo(CarWrapper &car) const;

    void render(const std::string &tag);
};
