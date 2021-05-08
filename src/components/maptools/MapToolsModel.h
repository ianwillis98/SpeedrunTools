#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>

class MapToolsModel
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

    explicit MapToolsModel(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static MapToolsModel &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void setCarState(Vector location = Vector(0.0f, 0.0f, 0.0f),
                     Rotator rotation = Rotator(0, 0, 0),
                     Vector velocity = Vector(0.0f, 0.0f, 0.0f),
                     Vector angularVelocity = Vector(0.0f, 0.0f, 0.0f),
                     float boostAmount = 0.0f);

    void removeAllBalls();
    void spawnAndStopBall(Vector location);
};
