#pragma once

#include "LiveSplitModel.h"
#include "../PluginComponentBase.h"
#include "../../services/LiveSplitClient.h"

class LiveSplitComponent : public PluginComponentBase
{
private:
    static const std::string ConnectCVarName;
    static const std::string DisconnectCVarName;
    static const std::string StartOrSplitCVarName;
    static const std::string StartCVarName;
    static const std::string PauseCVarName;
    static const std::string ResumeCVarName;
    static const std::string ResetCVarName;
    static const std::string SplitCVarName;
    static const std::string SkipSplitCVarName;
    static const std::string UndoSplitCVarName;

private:
    LiveSplitModel &liveSplitModel;

public:
    explicit LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void render() override;

private:
    void renderConnectionStatus();
    void renderRemoteControls();
};
