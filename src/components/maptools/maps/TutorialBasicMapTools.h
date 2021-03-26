#pragma once

#include "../MapToolsBase.h"

class TutorialBasicMapTools : public MapToolsBase
{
public:
    explicit TutorialBasicMapTools(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;
};

