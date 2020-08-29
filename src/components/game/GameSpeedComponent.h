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

    bool isComponentEnabled();
    void setComponentEnabled(bool enabled);

private:
    void onComponentEnabledChanged();

    float getSvSoccarGameSpeed();
    void setSvSoccarGameSpeed(float Speed);
    void onSvSoccarGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void onGameSpeedChanged(const std::string &oldValue, const CVarWrapper &cvar);
};
