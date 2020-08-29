#pragma once

#include "../../plugin/PluginComponent.h"

class GameSpeedComponent : public PluginComponent
{
public:
    explicit GameSpeedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    float getGameSpeed();
    void setGameSpeed(float gameSpeed);

private:
    std::unique_ptr<CVarWrapper> svSoccarGameSpeed;
    float getSvSoccarGameSpeed();
    void setSvSoccarGameSpeed(float Speed);
    void onSvSoccarGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar);

    std::unique_ptr<CVarWrapper> gameSpeed;
    void onGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar);
};
