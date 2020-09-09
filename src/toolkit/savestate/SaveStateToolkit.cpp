#include "SaveStateToolkit.h"

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), rewindStateComponent(plugin, 6.0f, 0.1f), saveStateComponent(plugin)
{

}

std::string SaveStateToolkit::title()
{
    return "Save States";
}

void SaveStateToolkit::onLoad()
{
    this->rewindStateComponent.onLoad();
    this->saveStateComponent.onLoad();

    this->plugin->cvarManager->registerNotifier("speedrun_savestate_rewind", [this](const std::vector<std::string> &commands) {
        this->rewindStateComponent.rewind();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);

    this->plugin->cvarManager->registerCvar("speedrun_savestate_rewindlength", "6.0", "Rewind length")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                this->rewindStateComponent.setRewindLength(cvar.getFloatValue());
            });

    this->plugin->cvarManager->registerCvar("speedrun_savestate_rewindsaveinterval", "0.1", "Rewind save interval")
            .addOnValueChanged([this](const std::string &oldValue, CVarWrapper cvar) {
                this->rewindStateComponent.setRewindSaveInterval(cvar.getFloatValue());
            });

    this->plugin->cvarManager->registerNotifier("speedrun_savestate_save", [this](const std::vector<std::string> &commands) {
        this->saveStateComponent.save();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("speedrun_savestate_load", [this](const std::vector<std::string> &commands) {
        this->saveStateComponent.load();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateToolkit::onUnload()
{
    this->rewindStateComponent.onUnload();
    this->saveStateComponent.onUnload();
}

void SaveStateToolkit::render()
{
    ImGui::Spacing();

    ImGui::Text("Save States Toolkit allows you to save the current game state to be loaded back or rewound for practice.");
    ImGui::Text("The following tools will only work in freeplay and workshop maps.");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->rewindStateComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->saveStateComponent.render();

    ImGui::Spacing();
    ImGui::Separator();
}
