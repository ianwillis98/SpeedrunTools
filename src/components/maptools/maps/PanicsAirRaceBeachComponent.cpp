#include "PanicsAirRaceBeachComponent.h"

PanicsAirRaceBeachComponent::PanicsAirRaceBeachComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          panicsAirRaceBeachAutoSplitterComponent(plugin)
{
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsbeach_reset", [this](const std::vector<std::string> &commands) {
        this->resetMap();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    for (int i = 1; i <= 11; i++)
    {
        std::string notifier = "speedrun_maptools_panicsbeach_cp" + std::to_string(i);
        this->plugin->cvarManager->registerNotifier(notifier, [this, i](const std::vector<std::string> &commands) {
            this->teleportToCheckpoint(i);
        }, "", PERMISSION_PAUSEMENU_CLOSED);
    }
}
void PanicsAirRaceBeachComponent::render()
{
    if (ImGui::TreeNodeEx("Checkpoints", ImGuiTreeNodeFlags_DefaultOpen))
    {
        this->renderPracticeSegments();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
    if (ImGui::TreeNodeEx("Auto Splitter", ImGuiTreeNodeFlags_DefaultOpen))
    {
        this->panicsAirRaceBeachAutoSplitterComponent.render();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
}

void PanicsAirRaceBeachComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->panicsAirRaceBeachAutoSplitterComponent.onEvent(eventName, post, params);
}

void PanicsAirRaceBeachComponent::renderPracticeSegments()
{
    ImGui::BeginChild("Checkpoints", ImVec2(300, 200), true);
    ImGui::Columns(2);
    if (ImGui::Button("Reset Map", ImVec2(-FLT_MIN, 0.0f)))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->resetMap();
        });
    }
    ImGui::NextColumn();
    for (int i = 1; i <= 11; i++)
    {
        char buf[32];
        sprintf(buf, "Checkpoint %02d", i);
        if (ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f)))
        {
            this->plugin->gameWrapper->Execute([this, i](GameWrapper *gw) {
                this->teleportToCheckpoint(i);
            });
        }
        ImGui::NextColumn();
    }
    ImGui::EndChild();
}

void PanicsAirRaceBeachComponent::resetMap()
{
    this->mapToolsModel.resetPlayers();
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint(int checkpoint)
{
    if (checkpoint == 1)
    {
        this->setCheckpointAndCount(0, 30);
        this->mapToolsModel.setCarState(Vector(11429.07f, -25964.96f, 50.0f), Rotator(-100, 3968, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 2)
    {
        this->setCheckpointAndCount(1, 39);
        this->mapToolsModel.setCarState(Vector(7217.72f, -16505.14, 0.0f), Rotator(-100, 12896, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 3)
    {
        this->setCheckpointAndCount(2, 61);
        this->mapToolsModel.setCarState(Vector(1581.56f, 793.88, 20.0f), Rotator(-100, -16640, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 4)
    {
        this->setCheckpointAndCount(3, 70);
        this->mapToolsModel.setCarState(Vector(-4065.12f, -12098.14, 70.0f), Rotator(-100, 19840, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 5)
    {
        this->setCheckpointAndCount(4, 76);
        this->mapToolsModel.setCarState(Vector(-6041.78f, 3165.77f, 0.0f), Rotator(-100, 23648, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 6)
    {
        this->setCheckpointAndCount(5, 84);
        this->mapToolsModel.setCarState(Vector(10414.92f, 5010.13f, 0.0f), Rotator(-100, -8064, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 7)
    {
        this->setCheckpointAndCount(6, 91);
        this->mapToolsModel.setCarState(Vector(17088.68f, 9103.98f, 110.0f), Rotator(-100, 26048, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 8)
    {
        this->setCheckpointAndCount(7, 118);
        this->mapToolsModel.setCarState(Vector(12386.14f, 15565.47f, 110.0f), Rotator(-100, -4128, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 9)
    {
        this->setCheckpointAndCount(8, 126);
        this->mapToolsModel.setCarState(Vector(10192.17f, 21147.19f, 0.0f), Rotator(-100, 21472, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 10)
    {
        this->setCheckpointAndCount(9, 155);
        this->mapToolsModel.setCarState(Vector(-868.84, 13827.73f, 0.0f), Rotator(-100, 31648, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
    else if (checkpoint == 11)
    {
        this->setCheckpointAndCount(10, 172);
        this->mapToolsModel.setCarState(Vector(-13317.81, 7834.1f, 0.0f), Rotator(-100, -21824, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
    }
}

void PanicsAirRaceBeachComponent::setCheckpointAndCount(int checkpoint, int count)
{
    std::vector<KismetSequenceVariable> kismetVars = this->mapToolsModel.getKismetVars();
    for (auto &var : kismetVars)
    {
        if (var.getName() == "Player1CPCount")
        {
            var.setIntValue(checkpoint);
            var.updateMainSequenceValue();
        }
        if (var.getName() == "Player1Count")
        {
            var.setIntValue(count);
            var.updateMainSequenceValue();
        }
    }
}
