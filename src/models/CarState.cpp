#include <imgui.h>
#include <cmath>
#include "CarState.h"

CarState::CarState(CarWrapper &car)
{
    if (car.IsNull()) return;

    this->location = car.GetLocation();
    this->rotation = car.GetRotation();
    this->velocity = car.GetVelocity();
    this->angularVelocity = car.GetAngularVelocity();

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    this->boostAmount = boost.GetCurrentBoostAmount();
}

CarState::CarState(Vector location, Rotator rotation, Vector velocity, Vector angularVelocity, float boostAmount)
        : location(location),
          rotation(rotation),
          velocity(velocity),
          angularVelocity(angularVelocity),
          boostAmount(boostAmount)
{

}


void CarState::applyTo(CarWrapper &car) const
{
    if (car.IsNull()) return;

    car.SetLocation(this->location);
    car.SetRotation(this->rotation);
    car.SetVelocity(this->velocity);
    car.SetAngularVelocity(this->angularVelocity, false);

    BoostWrapper boost = car.GetBoostComponent();
    if (boost.IsNull()) return;

    boost.SetBoostAmount(this->boostAmount);
}

bool CarState::render()
{
    ImGui::PushID(this);

    bool hasChanged = false;

    if (ImGui::TreeNodeEx("Car State (click any value to edit)", ImGuiTreeNodeFlags_DefaultOpen))
    {
        float positionArray[3] = {this->location.X, this->location.Y, this->location.Z};
        if (ImGui::InputFloat3("position (x,y,z)", positionArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            this->location = Vector(positionArray[0], positionArray[1], positionArray[2]);
            hasChanged = true;
        }

        float velocityArray[3] = {this->velocity.X, this->velocity.Y, this->velocity.Z};
        if (ImGui::InputFloat3("velocity (x,y,z)", velocityArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            this->velocity = Vector(velocityArray[0], velocityArray[1], velocityArray[2]);
            hasChanged = true;
        }

        int rotationArray[3] = {this->rotation.Pitch, this->rotation.Yaw, this->rotation.Roll};
        if (ImGui::InputInt3("rotation (pitch,yaw,roll)", rotationArray, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            this->rotation = Rotator(rotationArray[0], rotationArray[1], rotationArray[2]);
            hasChanged = true;
        }

        float boost = this->boostAmount;
        boost *= 100.0f;
        if (ImGui::InputFloat("boost", &boost, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
        {
            this->boostAmount = boost / 100.0f;
            hasChanged = true;
        }

        float speed = std::sqrt(this->velocity.X * this->velocity.X + this->velocity.Y * this->velocity.Y + this->velocity.Z * this->velocity.Z);
        ImGui::ProgressBar(speed / 2300.0f, ImVec2(0.f, 0.f), std::to_string(speed).c_str());
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::Text("speed");

        ImGui::TreePop();
    }

    ImGui::PopID();

    return hasChanged;
}
