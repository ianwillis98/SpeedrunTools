#include "AutoSplitterComponent.h"
#include "autosplitters/NullAutoSplitter.h"
#include "autosplitters/AutoSplitterFactory.h"

AutoSplitterComponent::AutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          liveSplitClient(LiveSplitClient::getInstance()),
          feedbackMessage("Waiting for connection to LiveSplit..."),
          autoSplitter(std::make_unique<NullAutoSplitter>())
{

}

void AutoSplitterComponent::onLoad()
{

}

void AutoSplitterComponent::render()
{
    ImGui::Spacing();

    ImGui::Text("Auto Splitter:");
    ImGui::Spacing();

    static int ci = 0;
    if (ImGui::Combo("map", &ci, AutoSplitterMap::mapTitles, AutoSplitterMap::maps.size()))
    {
        this->autoSplitter = AutoSplitterFactory::getInstance(this->plugin)
                .getAutoSplitterForMap(AutoSplitterMap::mapNames[ci]);
    }
}

void AutoSplitterComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->autoSplitter->onEvent(eventName, post, params);
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && !post)
    {
        if (this->liveSplitClient.getConnectionState() == ConnectionState::Connected || true)
        {
            if (this->autoSplitter->update())
            {
                if (this->autoSplitter->shouldTimerStart()) this->start();
                if (this->autoSplitter->shouldTimerSplit()) this->split();
                if (this->autoSplitter->shouldTimerReset()) this->reset();
            }
        }
    }
}

void AutoSplitterComponent::start()
{
    this->liveSplitClient.start([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'start' message was successfully sent." :
                                "Error while sending message 'start' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void AutoSplitterComponent::split()
{
    this->liveSplitClient.split([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'split' message was successfully sent." :
                                "Error while sending message 'split' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void AutoSplitterComponent::reset()
{
    this->liveSplitClient.reset([this](const int &errorCode, const std::string &errorMessage) {
        this->feedbackMessage = (errorCode == 0) ? "'reset' message was successfully sent." :
                                "Error while sending message 'reset' (" + std::to_string(errorCode) + ") \"" + errorMessage + "\".";
        this->log(this->feedbackMessage);
    });
}

void AutoSplitterComponent::log(const std::string &message)
{
    this->plugin->cvarManager->log("Auto Splitter: " + message);
    this->plugin->gameWrapper->Execute([this, message](GameWrapper *gw) {
        this->plugin->gameWrapper->LogToChatbox("Auto Splitter: " + message, "SPEEDRUNTOOLS");
    });
}
