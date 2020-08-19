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
    void saveCurrentState();
    void loadSaveState();

    SaveStateBuffer rewindBuffer;
    std::shared_ptr<float> rewindLength;
    void setRewindLength(float length);
    void rewindState();
};
