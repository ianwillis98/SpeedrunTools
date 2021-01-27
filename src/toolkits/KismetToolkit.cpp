#include "KismetToolkit.h"

KismetToolkit::KismetToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkitBase(plugin),
          kismetViewComponent(plugin),
          kismetEditorComponent(plugin)
{

}

std::string KismetToolkit::title()
{
    return "Kismet";
}

void KismetToolkit::onLoad()
{
    this->kismetViewComponent.onLoad();
    this->kismetEditorComponent.onLoad();
}

void KismetToolkit::render()
{
//    this->kismetViewComponent.render();
    ImGuiExtensions::BigSpacing();
    this->kismetEditorComponent.render();
}

void KismetToolkit::onEvent(const std::string &eventName, bool post, void *params)
{
    this->kismetViewComponent.onEvent(eventName, post, params);
    this->kismetEditorComponent.onEvent(eventName, post, params);
}
