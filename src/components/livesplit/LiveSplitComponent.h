#pragma once

#include "../PluginComponentBase.h"
#include "../../services/LiveSplitClient.h"

class LiveSplitComponent : public PluginComponentBase
{
public:
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
    LiveSplitClient &liveSplitClient;
    std::string feedbackMessage;

public:
    explicit LiveSplitComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onLoad() override;
    void render() override;

private:
    void connect();
    void disconnect();

    void startOrSplit();

    void start();
    void pause();
    void resume();
    void reset();

    void split();
    void skipSplit();
    void undoSplit();

    void log(const std::string &message);
};
