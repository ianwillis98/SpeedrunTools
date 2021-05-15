#include "MapToolsModel.h"
#include "../../models/CarState.h"

MapToolsModel &MapToolsModel::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static MapToolsModel instance(plugin);
    return instance;
}

MapToolsModel::MapToolsModel(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

std::vector<KismetSequenceVariable> MapToolsModel::getKismetVars()
{
    std::vector<KismetSequenceVariable> kismetVars;

    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address != NULL)
    {
        auto vars = sequence.GetAllSequenceVariables(false);

        for (auto &var : vars)
        {
            kismetVars.emplace_back(this->plugin, var.second);
        }
    }

    return kismetVars;
}

void MapToolsModel::resetPlayers()
{
    ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
    if (serverWrapper.IsNull()) return;

    serverWrapper.ResetPlayers();
}

void MapToolsModel::setCarState(Vector location, Rotator rotation, Vector velocity, Vector angularVelocity, float boostAmount)
{
    ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
    if (serverWrapper.IsNull()) return;

    CarWrapper carWrapper = serverWrapper.GetGameCar();
    if (carWrapper.IsNull()) return;

    CarState newCarState(location, rotation, velocity, angularVelocity, boostAmount);
    newCarState.applyTo(carWrapper);
}

void MapToolsModel::removeAllBalls()
{
    ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
    if (serverWrapper.IsNull()) return;

    std::vector<BallWrapper> ballsVector;
    auto ballsArrayWrapper = serverWrapper.GetGameBalls();
    for (const auto &ball : ballsArrayWrapper)
    {
        ballsVector.push_back(ball);
    }
    for (auto ball : ballsVector)
    {
        ball.DoDestroy();
    }
}

void MapToolsModel::spawnAndStopBall(Vector location)
{
    ServerWrapper serverWrapper = this->plugin->gameWrapper->GetGameEventAsServer();
    if (serverWrapper.IsNull()) return;

    serverWrapper.SpawnBall(location, true, false).Stop();
}

void MapToolsModel::isPlayerInsideCube(Vector corner1, Vector corner2)
{

}
