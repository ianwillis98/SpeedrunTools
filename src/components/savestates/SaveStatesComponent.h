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
    GameState gameSaveState;

public:
    explicit SaveStatesComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void saveCurrentGameState();
    void loadPreviousGameState();
};