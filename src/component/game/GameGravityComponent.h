#pragma once

#include "../PluginComponent.h"

class GameGravityComponent : public PluginComponent
{
public:
    explicit GameGravityComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    float getGameGravity();
    void setGameGravity(float gravity);
};
