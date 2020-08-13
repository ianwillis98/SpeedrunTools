#pragma once

#include "../PluginToolkit.h"
#include "../../models/CarState.h"
#include "../../models/BallState.h"

// save car state
// save ball state
// save both at same time (override ?)
// revert in time (~5 seconds?)

class SaveStateToolkit : public PluginToolkit
{
public:
    explicit SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    CarState carSaveState;
    bool isCarStateSaved;

    BallState ballSaveState;
    bool isBallStateSaved;

    float rewindLength;
    std::vector<CarState> rewindCarStates;
    std::vector<BallState> rewindBallStates;

    void saveCarState();
    void loadCarState();

    void saveBallState();
    void loadBallState();

    void setRewindLength(float length);
    void rewindCarState();
    void rewindBallState();
};
