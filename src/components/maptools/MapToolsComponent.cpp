#include "MapToolsComponent.h"

#include <utility>

MapToolsComponent::MapToolsComponent(NetcodePlugin *plugin, std::shared_ptr<AutoSplitterComponent> component,
                                     std::string mapName, std::string cVarName, int numCheckpoints)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          kismetModel(KismetModel::getInstance(plugin)),
          autoSplitterComponent(std::move(std::move(component))),
          mapName(std::move(mapName)),
          cVarName(std::move(cVarName)),
          numCheckpoints(numCheckpoints)
{
    this->createResetNotifier();
    this->createCheckpointNotifiers();
}

void MapToolsComponent::createResetNotifier()
{
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_" + this->cVarName + "_reset", [this](const std::vector<std::string> &commands) {
        this->autoSplitterComponent->onMapReset();
        this->resetMap();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
}

void MapToolsComponent::createCheckpointNotifiers()
{
    for (int i = 1; i <= this->numCheckpoints; i++)
    {
        std::string notifier = "speedrun_maptools_" + this->cVarName + "_cp" + std::to_string(i);
        this->plugin->cvarManager->registerNotifier(notifier, [this, i](const std::vector<std::string> &commands) {
            this->checkpoint(i);
        }, "", PERMISSION_PAUSEMENU_CLOSED);
    }
}

void MapToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->autoSplitterComponent->onEvent(eventName, post, params);
}

void MapToolsComponent::render()
{
    if (ImGui::TreeNodeEx(this->mapName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
    {
        this->renderGeneralMapTools();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
    if (this->numCheckpoints > 0)
    {
        if (ImGui::TreeNodeEx("Checkpoints", ImGuiTreeNodeFlags_DefaultOpen))
        {
            this->renderCheckpoints();
            ImGui::TreePop();
        }
        ImGuiExtensions::BigSeparator();
    }
    if (this->autoSplitterComponent != nullptr)
    {
        if (ImGui::TreeNodeEx("Auto Splitter", ImGuiTreeNodeFlags_DefaultOpen))
        {
            this->renderAutoSplitter();
            ImGui::TreePop();
        }
        ImGuiExtensions::BigSeparator();
    }
}

void MapToolsComponent::renderGeneralMapTools()
{
    if (ImGui::Button("Reset Map"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            if (this->autoSplitterComponent != nullptr) this->autoSplitterComponent->onMapReset();
            this->resetMap();
        });
    }
}

void MapToolsComponent::renderCheckpoints()
{
    ImGui::BeginChild("Checkpoints", ImVec2(300, 100), true);
    ImGui::Columns(2);
    for (int i = 1; i <= this->numCheckpoints; i++)
    {
        char buf[32];
        sprintf(buf, "Checkpoint %02d", i);
        if (ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f)))
        {
            this->plugin->gameWrapper->Execute([this, i](GameWrapper *gw) {
                this->checkpoint(i);
            });
        }
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::EndChild();
}

void MapToolsComponent::renderAutoSplitter()
{
    this->autoSplitterComponent->render();
}

void MapToolsComponent::renderCanvas(CanvasWrapper &canvasWrapper)
{
    this->autoSplitterComponent->renderCanvas(canvasWrapper);
}

void MapToolsComponent::disableAutoSplitter()
{
    autoSplitterComponent->disable();
}

std::string MapToolsComponent::getMapName()
{
    return this->mapName;
}

std::string MapToolsComponent::getCvar()
{
    return this->cVarName;
}
