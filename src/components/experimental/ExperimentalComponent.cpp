#include "ExperimentalComponent.h"

ExperimentalComponent::ExperimentalComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          fly(false),
          isBoostPressed(false),
          lockToCar(false),
          center(200, 200, 200),
          size(1750, 100, 1750),
          rotation(),
          rect(center, size, rotation)
{

}

void ExperimentalComponent::render()
{
    ImGui::Checkbox("Fly", &this->fly);
    ImGui::Checkbox("Lock to car", &this->lockToCar);

    this->rect.render();
}

void ExperimentalComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    CameraWrapper cameraWrapper = this->plugin->gameWrapper->GetCamera();
    if (cameraWrapper.IsNull()) return;

    Vector location = car.GetLocation();

    if (rect.contains(location)) canvasWrapper.SetColor(0, 255, 0, 255);
    else canvasWrapper.SetColor(255, 0, 0, 255);

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
            this->rotation = Rotator(0, car.GetRotation().Yaw, 0);
            this->rect = Rect3d(this->center, this->size, this->rotation);
        }
    }
}


