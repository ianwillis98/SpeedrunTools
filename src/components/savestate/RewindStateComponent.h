#pragma once

#include "../../plugin/PluginComponent.h"
#include "RewindBuffer.h"

class RewindStateComponent : public PluginComponent
{
public:
    explicit RewindStateComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void onUnload() override;
    void render() override;

    void rewind();

private:
    void onPhysicsTick();

    bool isComponentEnabled();
    void setComponentEnabled(bool enabled);
    void onComponentEnabledChanged();

    float getRewindLength();
    void setRewindLength(float length);
    void onRewindLengthChanged();

    float getRewindSaveInterval();
    void setRewindSaveInterval(float interval);

    float previousSaveTime;
    RewindBuffer rewindBuffer;
};
