#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>

class CVarFunctions
{
public:
    static void createCVarReflection(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &newCVarName, const std::string &existingCVarName);
};
