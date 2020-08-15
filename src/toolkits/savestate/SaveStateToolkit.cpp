#include <cmath>
#include "SaveStateToolkit.h"
#include "../../services/MultiEventHooker.h"

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin)
{
    this->isCarStateSaved = false;
    this->isBallStateSaved = false;
    this->rewindLength = 6.0f;
}

std::string SaveStateToolkit::title()
{
    return "Save States";
}

void SaveStateToolkit::onLoad()
{
//    this->plugin->cvarManager->registerCvar("fpt_ss_rewindlength", "6.0", "Save state rewind length", true, true, 1.0f, true, 15.0f, true);

    MultiEventHooker::getInstance().hookEvent(plugin, "Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &evenName) {
        if (!this->plugin->gameWrapper->IsInFreeplay()) return;

        CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
        if (car.IsNull()) return;

        ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (server.IsNull()) return;

        BallWrapper ball = server.GetBall();
        if (ball.IsNull()) return;

        if (this->rewindCarStates.size() >= 120 * this->rewindLength)
        {
            this->rewindCarStates.erase(this->rewindCarStates.begin());
        }
        if (this->rewindBallStates.size() >= 120 * this->rewindLength)
        {
            this->rewindBallStates.erase(this->rewindBallStates.begin());
        }
        this->rewindCarStates.emplace_back(car);
        this->rewindBallStates.emplace_back(ball);
    });

    this->plugin->cvarManager->registerNotifier("fpt_ss_savecar", [this](const std::vector<std::string> &commands) {
        this->saveCarState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_loadcar", [this](const std::vector<std::string> &commands) {
        this->loadCarState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_saveball", [this](const std::vector<std::string> &commands) {
        this->saveBallState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_loadball", [this](const std::vector<std::string> &commands) {
        this->loadBallState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_saveboth", [this](const std::vector<std::string> &commands) {
        this->saveCarState();
        this->saveBallState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_loadboth", [this](const std::vector<std::string> &commands) {
        this->loadCarState();
        this->loadBallState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_rewindcar", [this](const std::vector<std::string> &commands) {
        this->rewindCarState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_rewindball", [this](const std::vector<std::string> &commands) {
        this->rewindCarState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("fpt_ss_rewindboth", [this](const std::vector<std::string> &commands) {
        this->rewindCarState();
        this->rewindBallState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateToolkit::onUnload()
{

}

void SaveStateToolkit::render()
{
    ImGui::Text("hello");
}

void SaveStateToolkit::saveCarState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    this->carSaveState = CarState(car);
    this->isCarStateSaved = true;
}

void SaveStateToolkit::loadCarState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (!this->isCarStateSaved) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    this->carSaveState.applyTo(car);
}

void SaveStateToolkit::saveBallState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    BallWrapper ball = this->plugin->gameWrapper->GetGameEventAsServer().GetBall();
    if (ball.IsNull()) return;

    this->ballSaveState = BallState(ball);
    this->isBallStateSaved = true;
}

void SaveStateToolkit::loadBallState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (!this->isBallStateSaved) return;

    BallWrapper ball = this->plugin->gameWrapper->GetGameEventAsServer().GetBall();
    if (ball.IsNull()) return;

    this->ballSaveState.applyTo(ball);
}

void SaveStateToolkit::setRewindLength(float length)
{
    float clamped = std::fmax(1.0, std::fmin(15.0f, length));
    this->rewindLength = clamped;
    this->rewindCarStates.clear();
    this->rewindBallStates.clear();
}

void SaveStateToolkit::rewindCarState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (this->rewindCarStates.empty()) return;

    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    this->rewindCarStates[0].applyTo(car);
    this->rewindCarStates.resize(1);
}

void SaveStateToolkit::rewindBallState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (this->rewindBallStates.empty()) return;

    BallWrapper ball = this->plugin->gameWrapper->GetGameEventAsServer().GetBall();
    if (ball.IsNull()) return;

    this->rewindBallStates[0].applyTo(ball);
    this->rewindBallStates.resize(1);
}
