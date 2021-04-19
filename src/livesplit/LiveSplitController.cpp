#include "LiveSplitController.h"

#include <utility>

LiveSplitController::LiveSplitController(BakkesMod::Plugin::BakkesModPlugin *plugin, std::shared_ptr<LiveSplitModel> model)
        : PluginController(plugin),
          model(std::move(model)),
          connectView(plugin)
{
    this->connectView.setOnConnectButtonClickCallback([this]() {
        this->connectView.setConnecting(true);
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->model->connect([this](bool success, const std::string &status) {
                this->connectView.setConnecting(false);
            });
        });
    });
}

void LiveSplitController::onLoad()
{

}

void LiveSplitController::render()
{
    if (!this->model->isConnected())
    {
        this->connectView.render();
    }
}
