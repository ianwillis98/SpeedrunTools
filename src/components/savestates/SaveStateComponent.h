#pragma once

#include "../PluginComponentBase.h"
#include "../../models/GameState.h"

class SaveStateComponent : public PluginComponentBase
{
private:
    bool isGameStateSaved;
    GameState gameSaveState;

public:
    explicit SaveStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void saveCurrentGameState();
    void loadPreviousGameState();
};
