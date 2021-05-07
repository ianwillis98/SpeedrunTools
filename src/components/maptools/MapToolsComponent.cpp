#include "MapToolsComponent.h"
#include "maps/TutorialBasicComponent.h"
#include "maps/TutorialAdvancedComponent.h"
#include "maps/LethsNeonRingsMapToolsComponent.h"

MapToolsComponent::MapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          supportedMaps(),
          isMapToolLoaded(false),
          comboIndex(0)
{
    this->supportedMaps.emplace_back("Tutorial Basic", std::make_unique<TutorialBasicComponent>(plugin));
    this->supportedMaps.emplace_back("Tutorial Advanced", std::make_unique<TutorialAdvancedComponent>(plugin));
    this->supportedMaps.emplace_back("Leths Neon Rings", std::make_unique<LethsNeonRingsMapToolsComponent>(plugin));
    this->isMapToolLoaded = true;
}

void MapToolsComponent::render()
{
    ImGui::PushID(this);

    ImGuiExtensions::BigSpacing();

    std::vector<const char *> mapNames;
    for (auto &supportedMap : this->supportedMaps)
    {
        mapNames.push_back(supportedMap.first.c_str());
    }
    int oldIndex = this->comboIndex;
    if (ImGui::Combo("map", &comboIndex, mapNames.data(), mapNames.size()))
    {
        this->isMapToolLoaded = false;
        this->plugin->gameWrapper->Execute([this, oldIndex](GameWrapper *gw) {
//            this->supportedMaps.at(oldIndex).second->onUnload();
//            this->supportedMaps.at(comboIndex).second->onLoad();
//            this->isMapToolLoaded = true;
        });
    }

    ImGuiExtensions::BigSeparator();

    if (this->isMapToolLoaded) this->supportedMaps.at(comboIndex).second->render();

    ImGui::PopID();
}

void MapToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    if (this->isMapToolLoaded) this->supportedMaps.at(comboIndex).second->onEvent(eventName, post, params);
}
