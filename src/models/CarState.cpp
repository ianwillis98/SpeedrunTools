#include "CarState.h"

CarState::CarState(CarWrapper &car)
{
    if (car.IsNull()) return;

    this->position = car.GetLocation();
    this->rotation = car.GetRotation();
    this->velocity = car.GetVelocity();
    this->angularVelocity = car.GetAngularVelocity();

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    this->boostAmount = boost.GetCurrentBoostAmount();
}

CarState::CarState(Vector position, Rotator rotation, Vector velocity, Vector angularVelocity,
                   float boostAmount)
{
    this->position = position;
    this->rotation = rotation;
    this->velocity = velocity;
    this->angularVelocity = angularVelocity;
    this->boostAmount = boostAmount;
}

void CarState::applyTo(CarWrapper &car) const
{
    if (car.IsNull()) return;

    car.SetLocation(this->position);
    car.SetRotation(this->rotation);
    car.SetVelocity(this->velocity);
    car.SetAngularVelocity(this->angularVelocity, false);

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    boost.SetBoostAmount(this->boostAmount);
}
