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
    this->hitBoxes.emplace_back(1, Aabb(Vector(-3750, -23800, 7500), Vector(1600, -100, 1350)));
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
        if (hitBox.second.intersects(location)) canvasWrapper.SetColor(0, 255, 0, 255);
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
                    if (hitBox.first == this->segment && hitBox.second.intersects(location))
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
