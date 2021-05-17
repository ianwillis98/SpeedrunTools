#include <renderingtools/objects/RectangularPrism.h>
#include "ExperimentalComponent.h"

ExperimentalComponent::ExperimentalComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          fly(false),
          isBoostPressed(false),
          lockToCar(false),
          center(200, 200, 200),
          size(150, 150, 150),
          rotation(),
          rect(center, size, rotation, plugin)
{

}

void ExperimentalComponent::render()
{
    ImGui::Checkbox("Fly", &this->fly);
    ImGui::Checkbox("Lock to car", &this->lockToCar);

    float centerArray[3] = {this->center.X, this->center.Y, this->center.Z};
    if (ImGui::InputFloat3("corner (x,y,z)", centerArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        this->center = Vector(centerArray[0], centerArray[1], centerArray[2]);
        this->rect = Rect3d(this->center, this->size, this->rotation, plugin);
    }

    float sizeArray[3] = {this->size.X, this->size.Y, this->size.Z};
    if (ImGui::InputFloat3("size (x,y,z)", sizeArray, 2, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        this->size = Vector(sizeArray[0], sizeArray[1], sizeArray[2]);
        this->rect = Rect3d(this->center, this->size, this->rotation, plugin);
    }

    int rotationArray[3] = {this->rotation.Yaw, this->rotation.Pitch, this->rotation.Roll};
    if (ImGui::InputInt3("rotation (x,y,z)", rotationArray, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        this->rotation = Rotator(rotationArray[0], rotationArray[1], rotationArray[2]);
        this->rect = Rect3d(this->center, this->size, this->rotation, plugin);
    }
}

void ExperimentalComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    CameraWrapper cameraWrapper = this->plugin->gameWrapper->GetCamera();
    if (cameraWrapper.IsNull()) return;

    Vector location = car.GetLocation();

//    if (aabb.intersects(location)) canvasWrapper.SetColor(0, 255, 0, 255);
//    else canvasWrapper.SetColor(255, 0, 0, 255);
    canvasWrapper.SetColor(255, 0, 255, 255);
    rect.renderCanvas(canvasWrapper, cameraWrapper);
}

void ExperimentalComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post && params != nullptr)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        auto *controllerInput = (ControllerInput *) params;
        this->isBoostPressed = controllerInput->ActivateBoost;

    }
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
        if (car.IsNull()) return;

        if (this->fly && !this->isBoostPressed)
        {
            car.SetVelocity(Vector(0, 0, 0));
        }
        if (this->lockToCar)
        {
            this->center = car.GetLocation();
            this->rotation = car.GetRotation();
            this->rect = Rect3d(this->center, this->size, this->rotation, plugin);
        }
    }
}


