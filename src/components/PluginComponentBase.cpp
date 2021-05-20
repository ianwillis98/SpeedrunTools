#include "PluginComponentBase.h"

PluginComponentBase::PluginComponentBase(BakkesMod::Plugin::BakkesModPlugin *plugin) : plugin(plugin)
{

}

void PluginComponentBase::onEvent(const std::string &eventName, bool post, void *params)
{

}

void PluginComponentBase::render()
{

}

void PluginComponentBase::renderCanvas(CanvasWrapper &canvasWrapper)
{

}
