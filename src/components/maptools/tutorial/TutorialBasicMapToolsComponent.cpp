#include "TutorialBasicMapToolsComponent.h"
#include "TutorialBasicAutoSplitterComponent.h"

TutorialBasicMapToolsComponent::TutorialBasicMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<TutorialBasicAutoSplitterComponent>(plugin),
                            "Tutorial Basic", "tutorialbasic", 6)
{

}
void TutorialBasicMapToolsComponent::resetMap()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("start Park_P?Game=TAGame.GameInfo_Tutorial_TA?TutorialBasic");
}

void TutorialBasicMapToolsComponent::checkpoint(int checkpoint)
{
    if (checkpoint == 1)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 93.15f));
    }
    else if (checkpoint == 2)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 244.0f));
    }
    else if (checkpoint == 3)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, 4437.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 4752.0f, 208.0f));
    }
    else if (checkpoint == 4)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4667.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.333f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 3200.0f, 93.15f));
    }
    else if (checkpoint == 5)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4784.0f, 17.0f), Rotator(-100, 0, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 176.0f, 93.15f));
    }
    else if (checkpoint == 6)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -3207.0f, 17.0f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 0.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(0.0f, 0.0f, 93.15f));
        // line ~ (-400, 400) -800 0
    }
}
