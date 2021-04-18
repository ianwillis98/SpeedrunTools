#pragma once

#include "../../PluginComponentBase.h"
#include "../../autosplitter/runs/TutorialBasicAutoSplitterComponent.h"

class TutorialBasicComponent : public PluginComponentBase
{
private:
    TutorialBasicAutoSplitterComponent tutorialBasicAutoSplitterComponent;

public:
    explicit TutorialBasicComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;
    void onEvent(const std::string &eventName, bool post, void *params) override;
};

