#pragma once

#include "../PluginComponentBase.h"
#include "../../models/RewindBuffer.h"
#include "../../models/GameState.h"

class RewindComponent : public PluginComponentBase
{
private:
    RewindBuffer rewindBuffer;
    float previousSaveTime;

public:
    explicit RewindComponent(NetcodePlugin *plugin);

    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;

private:
    void rewindGameState();
};
