#pragma once

#include "../MapToolsBase.h"

class TutorialAdvancedMapTools : public MapToolsBase
{
public:
    explicit TutorialAdvancedMapTools(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;

private:
    void practiceSeg4();
    void practiceSeg5();
};
