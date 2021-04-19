#include "PluginModel.h"

PluginModel::PluginModel(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : plugin(plugin)
{

}

void PluginModel::onEvent(const std::string &eventName, bool post, void *params)
{

}
