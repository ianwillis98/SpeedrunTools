#include "CVarFunctions.h"

void CVarFunctions::createCVarReflection(BakkesMod::Plugin::BakkesModPlugin *plugin, const std::string &newCVarName, const std::string &existingCVarName)
{
    CVarWrapper existingCVar = plugin->cvarManager->getCvar(existingCVarName);
    CVarWrapper newCVar = plugin->cvarManager->registerCvar(newCVarName, existingCVar.getStringValue());

    // when ever one changes, update the other one with the new value
    newCVar.addOnValueChanged([=](const std::string &oldValue, CVarWrapper newCVar) {
        CVarWrapper existingCVar = plugin->cvarManager->getCvar(existingCVarName);
        if (existingCVar.getStringValue() != newCVar.getStringValue()) existingCVar.setValue(newCVar.getStringValue());
    });
    existingCVar.addOnValueChanged([=](const std::string &oldValue, CVarWrapper existingCVar) {
        CVarWrapper newCVar = plugin->cvarManager->getCvar(newCVarName);
        if (newCVar.getStringValue() != existingCVar.getStringValue()) newCVar.setValue(existingCVar.getStringValue());
    });
}