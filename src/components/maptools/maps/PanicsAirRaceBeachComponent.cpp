#include "PanicsAirRaceBeachComponent.h"

PanicsAirRaceBeachComponent::PanicsAirRaceBeachComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          panicsAirRaceBeachAutoSplitterComponent(plugin)
{

}
void PanicsAirRaceBeachComponent::render()
{
    ImGui::Text("PANIC'S AIR RACE BEACH MAP TOOLS");
    ImGui::Spacing();
    this->renderPracticeSegments();
    ImGuiExtensions::BigSeparator();

    ImGui::Text("PANIC'S AIR RACE BEACH AUTO SPLITTER");
    ImGui::Spacing();
    this->panicsAirRaceBeachAutoSplitterComponent.render();
}

void PanicsAirRaceBeachComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->panicsAirRaceBeachAutoSplitterComponent.onEvent(eventName, post, params);
}

void PanicsAirRaceBeachComponent::renderPracticeSegments()
{
    if (ImGui::Button("Reset Map"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->resetMap();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 1"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint1();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 2"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint2();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 3"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint3();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 4"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint4();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 5"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint5();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 6"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint6();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 7"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint7();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 8"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint8();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 9"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint9();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 10"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint10();
        });
    }
    if (ImGui::Button("Teleport to Checkpoint 11"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->teleportToCheckpoint11();
        });
    }
}

void PanicsAirRaceBeachComponent::resetMap()
{
    this->mapToolsModel.resetPlayers();
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint1()
{
    this->setCheckpointAndCount(0, 30);
    this->mapToolsModel.setCarState(Vector(11429.07f, -25964.96f, 50.0f), Rotator(-100, 3968, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint2()
{
    this->setCheckpointAndCount(1, 39);
    this->mapToolsModel.setCarState(Vector(7217.72f, -16505.14, 0.0f), Rotator(-100, 12896, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint3()
{
    this->setCheckpointAndCount(2, 61);
    this->mapToolsModel.setCarState(Vector(1581.56f, 793.88, 20.0f), Rotator(-100, -16640, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint4()
{
    this->setCheckpointAndCount(3, 70);
    this->mapToolsModel.setCarState(Vector(-4065.12f, -12098.14, 70.0f), Rotator(-100, 19840, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint5()
{
    this->setCheckpointAndCount(4, 76);
    this->mapToolsModel.setCarState(Vector(-6041.78f, 3165.77f, 0.0f), Rotator(-100, 23648, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint6()
{
    this->setCheckpointAndCount(5, 84);
    this->mapToolsModel.setCarState(Vector(10414.92f, 5010.13f, 0.0f), Rotator(-100, -8064, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint7()
{
    this->setCheckpointAndCount(6, 91);
    this->mapToolsModel.setCarState(Vector(17088.68f, 9103.98f, 110.0f), Rotator(-100, 26048, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint8()
{
    this->setCheckpointAndCount(7, 118);
    this->mapToolsModel.setCarState(Vector(12386.14f, 15565.47f, 110.0f), Rotator(-100, -4128, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint9()
{
    this->setCheckpointAndCount(8, 126);
    this->mapToolsModel.setCarState(Vector(10192.17f, 21147.19f, 0.0f), Rotator(-100, 21472, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint10()
{
    this->setCheckpointAndCount(9, 155);
    this->mapToolsModel.setCarState(Vector(-868.84, 13827.73f, 0.0f), Rotator(-100, 31648, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
}

void PanicsAirRaceBeachComponent::teleportToCheckpoint11()
{
    this->setCheckpointAndCount(10, 172);
    this->mapToolsModel.setCarState(Vector(-13317.81, 7834.1f, 0.0f), Rotator(-100, -21824, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
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
