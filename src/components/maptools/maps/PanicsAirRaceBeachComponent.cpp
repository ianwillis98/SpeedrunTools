#include "PanicsAirRaceBeachComponent.h"

PanicsAirRaceBeachComponent::PanicsAirRaceBeachComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          panicsAirRaceBeachAutoSplitterComponent(plugin)
{
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_reset", [this](const std::vector<std::string> &commands) {
        this->resetMap();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint1", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint1();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint2", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint2();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint3", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint3();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint4", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint4();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint5", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint5();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint6", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint6();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint7", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint7();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint8", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint8();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint9", [this](const std::vector<std::string> &commands) {
        this->teleportToCheckpoint9();
    }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint10",
                                                [this](const std::vector<std::string> &commands) {
                                                    this->teleportToCheckpoint10();
                                                }, "", PERMISSION_PAUSEMENU_CLOSED);
    this->plugin->cvarManager->registerNotifier("speedrun_maptools_panicsairracebeach_checkpoint11",
                                                [this](const std::vector<std::string> &commands) {
                                                    this->teleportToCheckpoint11();
                                                }, "", PERMISSION_PAUSEMENU_CLOSED);
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
        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
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
