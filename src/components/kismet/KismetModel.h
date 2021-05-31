#pragma once

#include "../../models/KismetVar.h"

class KismetModel
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;
    std::vector<KismetVar> kismetVars;

    explicit KismetModel(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static KismetModel &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEvent(const std::string &eventName, bool post, void *params);

    bool varExists(const std::string &name);
    KismetVar getVar(const std::string &name);
    void updateSequence(const KismetVar &kismetVar);

    std::vector<KismetVar> getKismetVars();

private:
    std::vector<KismetVar> loadKismetVars();

public:
    // quick access methods
    bool getBoolValue(const std::string &name);
    void setBoolValue(const std::string &name, bool value);

    int getIntValue(const std::string &name);
    void setIntValue(const std::string &name, int value);

    float getFloatValue(const std::string &name);
    void setFloatValue(const std::string &name, float value);

    std::string getStringValue(const std::string &name);
    void setStringValue(const std::string &name, const std::string &value);
};
