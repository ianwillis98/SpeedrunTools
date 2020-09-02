#pragma once

#include "../PluginComponent.h"

class GameSpeedComponent : public PluginComponent
{
public:
    explicit GameSpeedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    float getGameSpeed();
    void setGameSpeed(float speed);
};
