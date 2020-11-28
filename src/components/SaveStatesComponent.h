#pragma once

#include "../PluginComponent.h"
#include "../models/GameState.h"
#include "../models/RewindBuffer.h"

class SaveStatesComponent : public PluginComponent
{
private:
    bool isGameStateSaved;
    GameState gameSaveState;
    RewindBuffer rewindBuffer;
    float previousSaveTime;

public:
    explicit SaveStatesComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void render() override;
    void onEvent(std::string eventName, bool post, void *params) override;

private:
    void saveCurrentGameState();
    void loadPreviousGameState();
    void rewindGameState();

    void createSaveStateNotifiers();
    void createRewindCVarsAndNotifier();

    void renderSaveState();
    void renderRewind();
};
