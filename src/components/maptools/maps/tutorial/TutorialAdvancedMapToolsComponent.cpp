#include "TutorialAdvancedMapToolsComponent.h"
#include "../../autosplitter/runs/tutorial/TutorialAdvancedAutoSplitterComponent.h"

TutorialAdvancedMapToolsComponent::TutorialAdvancedMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : MapToolsComponent(plugin, std::make_shared<TutorialAdvancedAutoSplitterComponent>(plugin),
                            "Tutorial Advanced", "tutorialadvanced", 6)
{

}

void TutorialAdvancedMapToolsComponent::resetMap()
{
    this->plugin->gameWrapper->ExecuteUnrealCommand("start Park_P?Game=TAGame.GameInfo_Tutorial_TA?TutorialAdvanced");
}

void TutorialAdvancedMapToolsComponent::checkpoint(int checkpoints)
{
    if (checkpoints == 5)
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
    else if (checkpoints == 6)
    {
        this->mapToolsModel.setCarState(Vector(0.0f, -4859.0f, 17.01f), Rotator(-100, 16384, 0),
                                        Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), 1.0f);
        this->mapToolsModel.removeAllBalls();
        this->mapToolsModel.spawnAndStopBall(Vector(2559.98999f, -3167.98999f, 864.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(1919.98999f, 2720.01001f, 736.0f));
        this->mapToolsModel.spawnAndStopBall(Vector(-2432.01001f, 2720.01001f, 608.0f));
    }
}
