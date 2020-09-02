#pragma once

#include "../PluginToolkit.h"
#include "../../component/car/CarAnalysisComponent.h"
#include "../../component/ball/BallAnalysisComponent.h"

class AnalysisToolkit : public PluginToolkit
{
private:
    CarAnalysisComponent carAnalysisComponent;
    BallAnalysisComponent ballAnalysisComponent;

public:
    explicit AnalysisToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin);

    std::string title() override;
    void onLoad() override;
    void onUnload() override;
    void render() override;
};
