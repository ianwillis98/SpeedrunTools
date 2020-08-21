#pragma once

#include "../PluginToolkit.h"
#include "../../models/CarState.h"
#include "../../models/BallState.h"
#include "SaveState.h"
#include "SaveStateBuffer.h"

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
    SaveState saveState;
    bool isStateSaved;

    SaveStateBuffer rewindBuffer;
    std::shared_ptr<float> rewindLength;
    std::shared_ptr<float> rewindSaveInterval;

    void onPhysicsTick();

    void saveCurrentState();
    void loadSaveState();

    void rewindState();

    void setRewindLengthCVar(float length);
    void onRewindLengthCvarChanged(const std::string &oldValue, CVarWrapper cvar);

    void setRewindSaveIntervalCVar(float interval);
    void onRewindSaveIntervalChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void renderSaveStateView();
    void renderRewindView();
};
