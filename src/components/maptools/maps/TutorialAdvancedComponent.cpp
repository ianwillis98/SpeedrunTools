#include "TutorialAdvancedComponent.h"

TutorialAdvancedComponent::TutorialAdvancedComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          tutorialAdvancedAutoSplitterComponent(plugin)
{
    for (int i = 4; i <= 5; i++)
    {
        std::string notifier = "speedrun_maptools_tutorialadvanced_seg" + std::to_string(i);
        this->plugin->cvarManager->registerNotifier(notifier, [this, i](const std::vector<std::string> &commands) {
            this->practiceSegment(i);
        }, "", PERMISSION_PAUSEMENU_CLOSED);
    }
}

void TutorialAdvancedComponent::render()
{
    if (ImGui::TreeNodeEx("Tutorial Advanced", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Button("Load Advanced Tutorial"))
            this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
                this->loadAdvancedTutorial();
            });
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
    if (ImGui::TreeNodeEx("Practice Segments (must be in freeplay to work)", ImGuiTreeNodeFlags_DefaultOpen))
    {
        this->renderPracticeSegments();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
    if (ImGui::TreeNodeEx("Auto Splitter", ImGuiTreeNodeFlags_DefaultOpen))
    {
        tutorialAdvancedAutoSplitterComponent.render();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
}

void TutorialAdvancedComponent::renderPracticeSegments()
{
    ImGui::BeginChild("Checkpoints", ImVec2(300, 100), true);
    ImGui::Columns(2);
    for (int i = 4; i <= 5; i++)
    {
        char buf[32];
        sprintf(buf, "Segment %02d", i);
        if (ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f)))
        {
            this->plugin->gameWrapper->Execute([this, i](GameWrapper *gw) {
                this->practiceSegment(i);
            });
        }
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::EndChild();
}

void TutorialAdvancedComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->tutorialAdvancedAutoSplitterComponent.onEvent(eventName, post, params);
}

void TutorialAdvancedComponent::loadAdvancedTutorial()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("start Park_P?Game=TAGame.GameInfo_Tutorial_TA?TutorialAdvanced");
}

void TutorialAdvancedComponent::practiceSegment(int segment)
{
    if (segment == 4)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4859.0f, 17.01f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(2048.0f, 960.0f, 416.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(1024.0f, 3008.0f, 512.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, -1600.0f, 416.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(-1024.0f, 1472.0f, 512.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(-2048.0f, -64.0f, 416.0f));
    }
    else if (segment == 5)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4859.0f, 17.01f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(2559.98999f, -3167.98999f, 864.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(1919.98999f, 2720.01001f, 736.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(-2432.01001f, 2720.01001f, 608.0f));
    }
}
