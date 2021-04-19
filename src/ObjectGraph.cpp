#include "ObjectGraph.h"

ObjectGraph::ObjectGraph(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : models(), tabs(),
          liveSplitModel(std::make_shared<LiveSplitModel>(plugin)),
          liveSplitController(std::make_shared<LiveSplitController>(plugin, liveSplitModel))
{
    // models
    this->models.push_back(this->liveSplitModel);

    // controllers
    this->tabs.emplace_back("LiveSplit", this->liveSplitController);
}
