#include <imgui.h>
#include <cmath>
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

void CarState::render()
{
    ImGui::PushID(this);

    float positionArray[3] = {this->position.X, this->position.Y, this->position.Z};
    ImGui::InputFloat3("position (x,y,z)", positionArray, 2, ImGuiInputTextFlags_ReadOnly);

    int rotationArray[3] = {this->rotation.Pitch, this->rotation.Yaw, this->rotation.Roll};
    ImGui::InputInt3("rotation (pitch,yaw,roll)", rotationArray, ImGuiInputTextFlags_ReadOnly);

    float velocityArray[3] = {this->velocity.X, this->velocity.Y, this->velocity.Z};
    ImGui::InputFloat3("velocity (x,y,z)", velocityArray, 2, ImGuiInputTextFlags_ReadOnly);

    float speed = std::sqrt(this->velocity.X * this->velocity.X + this->velocity.Y * this->velocity.Y + this->velocity.Z * this->velocity.Z);
    ImGui::ProgressBar(speed / 2300.0f, ImVec2(0.f, 0.f), std::to_string(speed).c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("speed");

    float boost = this->boostAmount;
    boost *= 100.0f;
    ImGui::ProgressBar(boost / 100.0f, ImVec2(0.f, 0.f), std::to_string(boost).c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("boost");

    ImGui::PopID();
}
