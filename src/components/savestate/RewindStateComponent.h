#pragma once

#include "../../plugin/PluginComponent.h"
#include "RewindBuffer.h"

class RewindStateComponent : public PluginComponent
{
private:
    float previousSaveTime;
    RewindBuffer rewindBuffer;

public:
    explicit RewindStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    void rewind();

    float getRewindLength();
    void setRewindLength(float length);

    float getRewindSaveInterval();
    void setRewindSaveInterval(float interval);

    bool isComponentEnabled();
    void setComponentEnabled(bool enabled);

private:
    void onPhysicsTick();

    void onComponentEnabledChanged();

    void onRewindLengthChanged();
};
