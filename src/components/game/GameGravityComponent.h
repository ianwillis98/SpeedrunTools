#pragma once

#include "../../plugin/PluginComponent.h"

class GameGravityComponent : public PluginComponent
{
public:
    explicit GameGravityComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    float getGameGravity();
    void setGameGravity(float gravity);

    bool isComponentEnabled();
    void setComponentEnabled(bool enabled);

private:
    void onComponentEnabledChanged();

    float getSvSoccarGameGravity();
    void setSvSoccarGameGravity(float gravity);
    void onSvSoccarGameGravityChanged();

    void onGameGravityChanged();
};

