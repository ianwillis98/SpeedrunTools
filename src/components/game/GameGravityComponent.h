#pragma once

#include "../../plugin/PluginComponent.h"

class GameGravityComponent : public PluginComponent
{
public:
    static GameGravityComponent &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    explicit GameGravityComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    float getGameGravity();
    void setGameGravity(float gravity);

private:
    std::unique_ptr<CVarWrapper> svSoccarGameGravity;
    float getSvSoccarGameGravity();
    void setSvSoccarGameGravity(float gravity);
    void onSvSoccarGameGravityChanged(const std::string &oldValue, const CVarWrapper &cvar);

    std::unique_ptr<CVarWrapper> gameGravity;
    void onGameGravityChanged(const std::string &oldValue, const CVarWrapper &cvar);
};

