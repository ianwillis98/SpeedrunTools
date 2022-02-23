#include "SpeedJumpRings2AutoSplitterComponent.h"

SpeedJumpRings2AutoSplitterComponent::SpeedJumpRings2AutoSplitterComponent(NetcodePlugin *plugin)
        : AutoSplitterComponent(plugin),
          hitBoxes(),
          timer()
{
    this->hitBoxes.emplace_back(1, Rect3d(Vector(-2913, -23904, 8240), Vector(1650, 150, 1650), Rotator(0, 0, 0)));
    this->hitBoxes.emplace_back(2, Rect3d(Vector(5025, -34555, 12800), Vector(1650, 150, 1650), Rotator(0, 8192, 0)));
    this->hitBoxes.emplace_back(3, Rect3d(Vector(26619, -37756, 12944), Vector(1650, 150, 1650), Rotator(0, 20480, 0)));
    this->hitBoxes.emplace_back(4, Rect3d(Vector(40052, -13392, 11024), Vector(1650, 150, 1650), Rotator(0, 32768, 0)));
    this->hitBoxes.emplace_back(5, Rect3d(Vector(40434, 9489, 7712), Vector(1650, 150, 1650), Rotator(0, -24576, 0)));
    this->hitBoxes.emplace_back(6, Rect3d(Vector(18554, 31301, 8160), Vector(1650, 150, 1650), Rotator(0, -24576, 0)));
    this->hitBoxes.emplace_back(7, Rect3d(Vector(12840, 48442, 11568), Vector(1650, 150, 1650), Rotator(0, -24576, 0)));
    this->hitBoxes.emplace_back(8, Rect3d(Vector(-8038, 41965, 9104), Vector(1650, 150, 1650), Rotator(0, 4096, 0)));
    this->hitBoxes.emplace_back(9, Rect3d(Vector(-13277, 31803, 13280), Vector(1650, 150, 1650), Rotator(0, -12288, 0)));
    this->hitBoxes.emplace_back(10, Rect3d(Vector(-28747, 8828, 7200), Vector(1650, 150, 1650), Rotator(0, -4096, 0)));
}

void SpeedJumpRings2AutoSplitterComponent::onEnable()
{
    this->timer = this->kismetModel.getStringValue("displaytimer");
}

void SpeedJumpRings2AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        std::string previousTimer = this->timer;
        this->timer = this->kismetModel.getStringValue("displaytimer");

        if (this->segment == 0)
        {
            if (this->timer == "00:00" && previousTimer != "00:00")
            {
                this->start();
            }
        }
        else if (1 <= this->segment && this->segment <= 10)
        {
            CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
            if (car.IsNull()) return;

            Vector location = car.GetLocation();

            if (this->hitBoxes[this->segment - 1].second.contains(location))
            {
                this->split();
            }
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->segment == 11)
        {
            this->split();
        }
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining" && post)
    {
        this->kismetModel.setStringValue("displaytimer", ""); // in case they reset when timer is "0:00"
        this->reset();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset();
    }
}

void SpeedJumpRings2AutoSplitterComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
//    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
//
//    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
//    if (car.IsNull()) return;
//
//    CameraWrapper cameraWrapper = this->plugin->gameWrapper->GetCamera();
//    if (cameraWrapper.IsNull()) return;
//
//    Vector location = car.GetLocation();
//
//    for (auto &hitBox : hitBoxes)
//    {
//        if (hitBox.second.contains(location)) canvasWrapper.SetColor(0, 255, 0, 255);
//        else canvasWrapper.SetColor(255, 0, 0, 255);
//
//        hitBox.second.renderCanvas(canvasWrapper, cameraWrapper);
//    }
}

std::string SpeedJumpRings2AutoSplitterComponent::getStartDescription()
{
    return "The timer starts when the map's timer starts.";
}

std::string SpeedJumpRings2AutoSplitterComponent::getSplitDescription()
{
    return "The timer will split after passing the final ring of each section and when the timer stops(11 splits in total).";
}

std::string SpeedJumpRings2AutoSplitterComponent::getResetDescription()
{
    return "The timer will reset when the player presses the 'Reset Shot' binding or leaves the match.";
}

std::string SpeedJumpRings2AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 2 Auto Splitter (Debug)" << std::endl;
    ss << "timer = " << this->timer << std::endl;
    return ss.str();
}
