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
    static const bool DEFAULT_IS_REWIND_ACTIVE;
    static const float DEFAULT_REWIND_LENGTH;
    static const float DEFAULT_REWIND_SAVE_INTERVAL;

public:
    explicit SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;

private:
    SaveState saveState;
    bool isStateSaved;

    std::shared_ptr<bool> isRewindActive;
    std::shared_ptr<float> rewindLength;
    std::shared_ptr<float> rewindSaveInterval;
    float previousSaveTime;
    SaveStateBuffer rewindBuffer;

    void onPhysicsTick();

    void onSaveState();
    void onLoadState();

    void onRewindState();

    void setIsRewindActiveCVar(bool active);
    void onIsRewindActiveCVarChanged(const std::string &oldValue, const CVarWrapper& cvar);

    void setRewindLengthCVar(float length);
    void onRewindLengthCvarChanged(const std::string &oldValue, const CVarWrapper& cvar);

    void setRewindSaveIntervalCVar(float interval);
    void onRewindSaveIntervalChanged(const std::string &oldValue, const CVarWrapper &cvar);

    void renderRewindView();
    void renderSaveStateView();
};
