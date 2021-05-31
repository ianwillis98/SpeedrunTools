#include "KismetModel.h"

KismetModel::KismetModel(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : plugin(plugin), kismetVars()
{

}

KismetModel &KismetModel::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    static KismetModel instance(plugin);
    return instance;
}

void KismetModel::onEvent(const std::string &eventName, bool post, void *params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        this->kismetVars = this->loadKismetVars();
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.InitGame" && post)
    {
        this->plugin->gameWrapper->SetTimeout([this](GameWrapper *gw) {
            this->kismetVars = this->loadKismetVars();
        }, 1.0f);
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->kismetVars.clear();
    }
}

bool KismetModel::varExists(const std::string &name)
{
    for (auto &var : this->kismetVars)
    {
        if (var.getName() == name) return true;
    }
    return false;
}

KismetVar KismetModel::getVar(const std::string &name)
{
    for (auto &var : this->kismetVars)
    {
        if (var.getName() == name) return var;
    }
    return KismetVar(name);
}

void KismetModel::updateSequence(const KismetVar &kismetVar)
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto sequenceVars = sequence.GetAllSequenceVariables(false);

    auto sequenceVar = sequenceVars.find(kismetVar.getName());
    if (sequenceVar == sequenceVars.end()) return;

    if (kismetVar.getType() == KismetVarType::Bool)
    {
        sequenceVar->second.SetBool(kismetVar.getBoolValue());
    }
    else if (kismetVar.getType() == KismetVarType::Int)
    {
        sequenceVar->second.SetInt(kismetVar.getIntValue());
    }
    else if (kismetVar.getType() == KismetVarType::Float)
    {
        sequenceVar->second.SetFloat(kismetVar.getFloatValue());
    }
    else if (kismetVar.getType() == KismetVarType::String)
    {
        sequenceVar->second.SetString(kismetVar.getStringValue());
    }
}

std::vector<KismetVar> KismetModel::getKismetVars()
{
    return this->kismetVars;
}

std::vector<KismetVar> KismetModel::loadKismetVars()
{
    std::vector<KismetVar> loaded;

    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address != NULL)
    {
        auto vars = sequence.GetAllSequenceVariables(false);

        for (auto &var : vars)
        {
            loaded.emplace_back(var.second);
        }
    }

    return loaded;
}

bool KismetModel::getBoolValue(const std::string &name)
{
    return this->getVar(name).getBoolValue();
}

void KismetModel::setBoolValue(const std::string &name, bool value)
{
    KismetVar kismetVar = this->getVar(name);
    kismetVar.setBoolValue(value);
    this->updateSequence(kismetVar);
}

int KismetModel::getIntValue(const std::string &name)
{
    return this->getVar(name).getIntValue();
}

void KismetModel::setIntValue(const std::string &name, int value)
{
    KismetVar kismetVar = this->getVar(name);
    kismetVar.setIntValue(value);
    this->updateSequence(kismetVar);
}

float KismetModel::getFloatValue(const std::string &name)
{
    return this->getVar(name).getFloatValue();
}

void KismetModel::setFloatValue(const std::string &name, float value)
{
    KismetVar kismetVar = this->getVar(name);
    kismetVar.setFloatValue(value);
    this->updateSequence(kismetVar);
}

std::string KismetModel::getStringValue(const std::string &name)
{
    return this->getVar(name).getStringValue();
}

void KismetModel::setStringValue(const std::string &name, const std::string &value)
{
    KismetVar kismetVar = this->getVar(name);
    kismetVar.setStringValue(value);
    this->updateSequence(kismetVar);
}
