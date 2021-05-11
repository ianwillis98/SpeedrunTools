#include "TutorialBasicComponent.h"

TutorialBasicComponent::TutorialBasicComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          tutorialBasicAutoSplitterComponent(plugin)
{
    for (int i = 1; i <= 5; i++)
    {
        std::string notifier = "speedrun_maptools_tutorialbasic_seg" + std::to_string(i);
        this->plugin->cvarManager->registerNotifier(notifier, [this, i](const std::vector<std::string> &commands) {
            this->practiceSegment(i);
        }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    }
}

void TutorialBasicComponent::render()
{
    if (ImGui::Button("Load Basic Tutorial"))
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->loadBasicTutorial();
        });
    ImGuiExtensions::BigSeparator();
    if (ImGui::TreeNodeEx("Practice Segments (must be in freeplay to work)", ImGuiTreeNodeFlags_DefaultOpen))
    {
        this->renderPracticeSegments();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
    if (ImGui::TreeNodeEx("Auto Splitter", ImGuiTreeNodeFlags_DefaultOpen))
    {
        tutorialBasicAutoSplitterComponent.render();
        ImGui::TreePop();
    }
    ImGuiExtensions::BigSeparator();
}

void TutorialBasicComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    tutorialBasicAutoSplitterComponent.onEvent(eventName, post, params);
}

void TutorialBasicComponent::renderPracticeSegments()
{
    ImGui::BeginChild("Checkpoints", ImVec2(300, 100), true);
    ImGui::Columns(2);
    for (int i = 1; i <= 5; i++)
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

void TutorialBasicComponent::loadBasicTutorial()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("start Park_P?Game=TAGame.GameInfo_Tutorial_TA?TutorialBasic");
}

void TutorialBasicComponent::practiceSegment(int segment)
{
    if (segment == 1)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 93.15f));
    }
    else if (segment == 2)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 244.0f));
    }
    else if (segment == 3)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, 4437.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 4752.0f, 208.0f));
    }
    else if (segment == 4)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.333f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 3200.0f, 93.15f));
    }
    else if (segment == 5)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4784.0f, 17.0f), Rotator(-100, 0, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 176.0f, 93.15f));
    }
    else if (segment == 6)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -3207.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 93.15f));
        // line ~ (-400, 400) -800 0
    }
}
