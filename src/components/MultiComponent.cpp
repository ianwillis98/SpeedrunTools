#include "MultiComponent.h"

#include <utility>

MultiComponent::MultiComponent(BakkesMod::Plugin::BakkesModPlugin *plugin, std::vector<std::unique_ptr<PluginComponent>> components)
        : PluginComponentBase(plugin),
          components(std::move(components))
{

}

void MultiComponent::onLoad()
{
    for (auto &component : this->components)
    {
        component->onLoad();
    }
}

void MultiComponent::onUnload()
{
    for (auto &component : this->components)
    {
        component->onUnload();
    }
}

void MultiComponent::render()
{
    int i = 0;
    for (auto &component : this->components)
    {
        component->render();
        i++;
        if (i != this->components.size()) ImGuiExtensions::BigSeparator();
    }
}

void MultiComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    for (auto &component : this->components)
    {
        component->onEvent(eventName, post, params);
    }
}

