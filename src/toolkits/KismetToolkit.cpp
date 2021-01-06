#include "KismetToolkit.h"

KismetToolkit::KismetToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin),
          kismetViewComponent(plugin)
{

}

std::string KismetToolkit::title()
{
    return "Kismet";
}

void KismetToolkit::onLoad()
{
    this->kismetViewComponent.onLoad();
}

void KismetToolkit::render()
{
    this->kismetViewComponent.render();
}

void KismetToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->kismetViewComponent.onEvent(eventName, post, params);
}
