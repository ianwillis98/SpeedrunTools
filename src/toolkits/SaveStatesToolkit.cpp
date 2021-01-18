#include "SaveStatesToolkit.h"

SaveStatesToolkit::SaveStatesToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin),
          saveStateComponent(plugin),
          rewindComponent(plugin)
{

}

std::string SaveStatesToolkit::title()
{
    return "Save States";
}

void SaveStatesToolkit::onLoad()
{
    this->saveStateComponent.onLoad();
    this->rewindComponent.onLoad();
}

void SaveStatesToolkit::render()
{
    ImGuiExtensions::BigSpacing();

    this->saveStateComponent.render();
    ImGuiExtensions::BigSeparator();

    this->rewindComponent.render();
    ImGuiExtensions::BigSpacing();
}

void SaveStatesToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->saveStateComponent.onEvent(eventName, post, params);
    this->rewindComponent.onEvent(eventName, post, params);
}
