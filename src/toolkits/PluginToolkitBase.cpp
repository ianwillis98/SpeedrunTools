#include "PluginToolkitBase.h"

PluginToolkitBase::PluginToolkitBase(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

std::string PluginToolkitBase::title()
{
    return "";
}

void PluginToolkitBase::onLoad()
{

}

void PluginToolkitBase::onUnload()
{

}

void PluginToolkitBase::render()
{

}

void PluginToolkitBase::onEvent(const std::string &eventName, bool post, void *params)
{

}
