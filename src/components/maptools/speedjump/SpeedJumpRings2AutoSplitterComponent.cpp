#include "SpeedJumpRings2AutoSplitterComponent.h"

SpeedJumpRings2AutoSplitterComponent::SpeedJumpRings2AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : AutoSplitterComponent(plugin),
          hasUpdatedOnce(),
          hasUpdatedTwice(),
          currentLevel(),
          previousLevel(),
          currentDisplayTimer(),
          previousDisplayTimer(),
          segment(0),
          hitBoxes()
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

void SpeedJumpRings2AutoSplitterComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    CameraWrapper cameraWrapper = this->plugin->gameWrapper->GetCamera();
    if (cameraWrapper.IsNull()) return;

    Vector location = car.GetLocation();

    for (auto &hitBox : hitBoxes)
    {
        if (hitBox.second.contains(location)) canvasWrapper.SetColor(0, 255, 0, 255);
        else canvasWrapper.SetColor(255, 0, 0, 255);

        hitBox.second.renderCanvas(canvasWrapper, cameraWrapper);
    }
}

void SpeedJumpRings2AutoSplitterComponent::onEnable()
{
    this->hasUpdatedOnce = false;
    this->hasUpdatedTwice = false;
}

void SpeedJumpRings2AutoSplitterComponent::update(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        auto sequence = this->plugin->gameWrapper->GetMainSequence();
        if (sequence.memory_address == NULL) return;

        auto allVars = sequence.GetAllSequenceVariables(false);

        auto level = allVars.find("Level");
        if (level == allVars.end()) return;

        this->previousLevel = this->currentLevel;
        this->currentLevel = level->second.GetInt();

        auto displayTimer = allVars.find("displaytimer");
        if (displayTimer == allVars.end()) return;

        this->previousDisplayTimer = this->currentDisplayTimer;
        this->currentDisplayTimer = displayTimer->second.GetString();

        if (this->hasUpdatedOnce && !this->hasUpdatedTwice) this->hasUpdatedTwice = true;
        if (!this->hasUpdatedOnce) this->hasUpdatedOnce = true;

        if (this->hasUpdatedTwice)
        {
            this->plugin->cvarManager->log("seg,emt " + std::to_string(this->segment));

            if (this->segment == 0)
            {
                if (this->currentDisplayTimer == "00:00" && this->previousDisplayTimer != "00:00")
                {
                    this->segment++;
                    this->startTimer();
                }
            }
            else if (1 <= this->segment && this->segment <= 10)
            {
                CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
                if (car.IsNull()) return;

                Vector location = car.GetLocation();

                for (auto &hitBox : hitBoxes)
                {
                    if (hitBox.first == this->segment && hitBox.second.contains(location))
                    {
                        this->segment++;
                        this->splitTimer();
                    }
                }
            }
        }
    }
    if (eventName == "Function TAGame.GFxShell_TA.ShowModalObject" && post)
    {
        if (this->segment == 11)
        {
            this->segment++;
            this->splitTimer();
        }
    }
    if (eventName == "Function TAGame.GameEvent_TA.PlayerResetTraining")
    {
        this->segment = 0;
        this->resetTimer();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->hasUpdatedOnce = false;
        this->hasUpdatedTwice = false;
        if (this->segment > 0)
        {
            this->segment = 0;
            this->resetTimer();
        }
    }
}

std::string SpeedJumpRings2AutoSplitterComponent::getStartDescription()
{
    return AutoSplitterComponent::getStartDescription();
}

std::string SpeedJumpRings2AutoSplitterComponent::getSplitDescription()
{
    return AutoSplitterComponent::getSplitDescription();
}

std::string SpeedJumpRings2AutoSplitterComponent::getResetDescription()
{
    return AutoSplitterComponent::getResetDescription();
}

std::string SpeedJumpRings2AutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Speed Jump Rings 2 Auto Splitter (Debug)" << std::endl;
    ss << "hasUpdatedOnce = " << this->hasUpdatedOnce << std::endl;
    ss << "hasUpdatedTwice = " << this->hasUpdatedTwice << std::endl;
    ss << "currentLevel = " << this->currentLevel << std::endl;
    ss << "previousLevel = " << this->previousLevel << std::endl;
    ss << "currentDisplayTimer = " << this->currentDisplayTimer << std::endl;
    ss << "previousDisplayTimer = " << this->previousDisplayTimer << std::endl;
    return ss.str();
}
