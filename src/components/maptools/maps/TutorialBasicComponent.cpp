#include "TutorialBasicComponent.h"

TutorialBasicComponent::TutorialBasicComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          mapToolsModel(MapToolsModel::getInstance(plugin)),
          tutorialBasicAutoSplitterComponent(plugin)
{

}

void TutorialBasicComponent::render()
{
    if (ImGui::TreeNodeEx("Segments", ImGuiTreeNodeFlags_DefaultOpen))
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
    ImGui::Text("You must be in freeplay for these to work correctly");
    ImGui::Spacing();
    if (ImGui::Button("Practice Segment 1"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSegment1();
        });
    }
    if (ImGui::Button("Practice Segment 2"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSegment2();
        });
    }
    if (ImGui::Button("Practice Segment 3"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSegment3();
        });
    }
    if (ImGui::Button("Practice Segment 4"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSegment4();
        });
    }
    if (ImGui::Button("Practice Segment 5"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->practiceSegment5();
        });
    }
//    if (ImGui::Button("Practice Segment 6"))
//    {
//        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
//            this->practiceSegment6();
//        });
//    }
}

void TutorialBasicComponent::practiceSegment1()
{
    this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
    this->mapToolsModel.removeAllBalls();
    this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 93.15f));

}
void TutorialBasicComponent::practiceSegment2()
{
    this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
    this->mapToolsModel.removeAllBalls();
    this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 244.0f));
}

void TutorialBasicComponent::practiceSegment3()
{
    this->mapToolsModel.setCarState(Vector(0.0f, 4437.0f, 17.0f), Rotator(-100, 16384, 0), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
    this->mapToolsModel.removeAllBalls();
    this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 4752.0f, 208.0f));
}

void TutorialBasicComponent::practiceSegment4()
{
    this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                    Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.333f);
    this->mapToolsModel.removeAllBalls();
    this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 3200.0f, 93.15f));
}

void TutorialBasicComponent::practiceSegment5()
{
    this->mapToolsModel.setCarState(Vector(0.0f, -4784.0f, 17.0f), Rotator(-100, 0, 0), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
    this->mapToolsModel.removeAllBalls();
    this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 176.0f, 93.15f));
}

void TutorialBasicComponent::practiceSegment6()
{
    this->mapToolsModel.setCarState(Vector(0.0f, -3207.0f, 17.0f), Rotator(-100, 16384, 0), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
    this->mapToolsModel.removeAllBalls();
    this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 93.15f));
    // line ~ (-400, 400) -800 0
}
