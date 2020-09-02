#pragma once

#include "RewindBuffer.h"
#include "../PluginComponent.h"

class RewindStateComponent : public PluginComponent
{
private:
    RewindBuffer rewindBuffer;
    float rewindSaveInterval;
    float previousSaveTime;

public:
    RewindStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, float rewindLength, float rewindInterval);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    void rewind();

    float getRewindLength();
    void setRewindLength(float length);

    float getRewindSaveInterval() const;
    void setRewindSaveInterval(float interval);

private:
    void onPhysicsTick();
};
