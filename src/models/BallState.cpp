#include <imgui.h>
#include <cmath>
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

void BallState::render(const std::string &tag)
{
    ImGui::Text("Ball state:");

    float positionArray[3] = {this->position.X, this->position.Y, this->position.Z};
    ImGui::InputFloat3(("position (x,y,z)##" + tag).c_str(), positionArray, 2, ImGuiInputTextFlags_ReadOnly);

    int rotationArray[3] = {this->rotation.Pitch, this->rotation.Yaw, this->rotation.Roll};
    ImGui::InputInt3(("rotation (pitch,yaw,roll)##" + tag).c_str(), rotationArray, ImGuiInputTextFlags_ReadOnly);

    float velocityArray[3] = {this->velocity.X, this->velocity.Y, this->velocity.Z};
    ImGui::InputFloat3(("velocity (x,y,z)##" + tag).c_str(), velocityArray, 2, ImGuiInputTextFlags_ReadOnly);

    float speed = std::sqrt(this->velocity.X * this->velocity.X + this->velocity.Y * this->velocity.Y + this->velocity.Z * this->velocity.Z);
    ImGui::ProgressBar(speed / 2300.0f, ImVec2(0.f, 0.f), std::to_string(speed).c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("speed");
}
