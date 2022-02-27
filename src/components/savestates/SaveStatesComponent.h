#pragma once

#include "../PluginComponentBase.h"
#include "../../models/GameState.h"

class SaveStatesComponent : public PluginComponentBase
{
public:
    static const std::string SaveStateCVarName;
    static const std::string LoadStateCVarName;

private:
    bool isGameStateSaved;
    GameState savedGameState;

public:
    explicit SaveStatesComponent(NetcodePlugin *plugin);

    void render() override;

private:
    void saveCurrentGameState();
    void loadPreviousGameState();
};
