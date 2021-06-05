#pragma once

#include "../../AutoSplitterComponent.h"
#include "../../../../models/collision/Rect3d.h"

class SpeedJumpRings2AutoSplitterComponent : public AutoSplitterComponent
{
private:
    std::vector<std::pair<int, Rect3d>> hitBoxes;
    std::string timer;

public:
    explicit SpeedJumpRings2AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;
    void renderCanvas(CanvasWrapper &canvasWrapper) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};
