#pragma once

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include <string>

class HelperFunctions
{
public:
    static void createCVarReference(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string& newCVarName, const std::string& existingCVarName);
};
