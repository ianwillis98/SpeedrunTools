#include <imgui.h>
#include <cmath>
#include "BallState.h"
#include "../utils/ImGuiExtensions.h"

BallState::BallState() : position(), rotation(), velocity(), angularVelocity()
{

}

BallState::BallState(BallWrapper &ball)
{
    if (ball.IsNull()) return;

    this->position = ball.GetLocation();
    this->rotation = ball.GetRotation();
    this->velocity = ball.GetVelocity();
    this->angularVelocity = ball.GetAngularVelocity();
}

void BallState::applyTo(BallWrapper &ball) const
{
    if (ball.IsNull()) return;

    ball.SetLocation(this->position);
    ball.SetRotation(this->rotation);
    ball.SetVelocity(this->velocity);
    ball.SetAngularVelocity(this->angularVelocity, false);
}

bool BallState::render()
{
    ImGui::PushID(this);

    bool hasChanged = false;

    if (ImGui::TreeNodeEx("Ball State (click any value to edit)", ImGuiTreeNodeFlags_DefaultOpen))
    {
        float positionArray[3] = {this->position.X, this->position.Y, this->position.Z};
        if (ImGui::InputFloat3("position (x,y,z)", positionArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            this->position = Vector(positionArray[0], positionArray[1], positionArray[2]);
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

        float speed = std::sqrt(this->velocity.X * this->velocity.X + this->velocity.Y * this->velocity.Y + this->velocity.Z * this->velocity.Z);
        ImGui::ProgressBar(speed / 2300.0f, ImVec2(0.f, 0.f), std::to_string(speed).c_str());
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::Text("speed");

        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();

    ImGui::PopID();

    return hasChanged;
}
