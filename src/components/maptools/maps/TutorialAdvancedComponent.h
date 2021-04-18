#pragma once

#include "../../PluginComponentBase.h"

class TutorialAdvancedComponent : public PluginComponentBase
{
public:
    explicit TutorialAdvancedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;

private:
    void practiceSeg4();
    void practiceSeg5();
};
