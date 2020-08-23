#include "SaveStateToolkit.h"
#include "../../services/MultiEventHooker.h"
#include <utils/customrotator.h>

const bool SaveStateToolkit::DEFAULT_IS_REWIND_ACTIVE = true;
const float SaveStateToolkit::DEFAULT_REWIND_LENGTH = 6.0f;
const float SaveStateToolkit::DEFAULT_REWIND_SAVE_INTERVAL = 0.1f;

SaveStateToolkit::SaveStateToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginToolkit(plugin), isRewindActive(std::make_shared<bool>()), rewindLength(std::make_shared<float>()),
          rewindSaveInterval(std::make_shared<float>()), isStateSaved(false), rewindBuffer(rewindLength), previousSaveTime()
{

}

std::string SaveStateToolkit::title()
{
    return "Save States";
}

void SaveStateToolkit::onLoad()
{
    CVarWrapper isRewindActiveCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindactive", std::to_string(DEFAULT_IS_REWIND_ACTIVE),
                                                                             "Is rewind active");
    isRewindActiveCVar.bindTo(this->isRewindActive);
    isRewindActiveCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onIsRewindActiveCVarChanged(oldValue, cvar);
    });

    this->plugin->cvarManager->log("asdfasfdasdf its loading!");

    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindlength", std::to_string(DEFAULT_REWIND_LENGTH),
                                                                           "Rewind length");
    rewindLengthCVar.bindTo(this->rewindLength);
    rewindLengthCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onRewindLengthCvarChanged(oldValue, cvar);
    });

    CVarWrapper rewindSaveIntervalCVar = this->plugin->cvarManager->registerCvar("st_ss_rewindsaveinterval",
                                                                                 std::to_string(DEFAULT_REWIND_SAVE_INTERVAL),
                                                                                 "Rewind save interval");
    rewindSaveIntervalCVar.bindTo(this->rewindSaveInterval);
    rewindSaveIntervalCVar.addOnValueChanged([this](const std::string &oldValue, const CVarWrapper &cvar) {
        this->onRewindSaveIntervalChanged(oldValue, cvar);
    });

    MultiEventHooker::getInstance().hookEvent(plugin, "Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &evenName) {
        this->onPhysicsTick();
    });

    this->plugin->cvarManager->registerNotifier("st_ss_save", [this](const std::vector<std::string> &commands) {
        this->onSaveState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_load", [this](const std::vector<std::string> &commands) {
        this->onLoadState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
    this->plugin->cvarManager->registerNotifier("st_ss_rewind", [this](const std::vector<std::string> &commands) {
        this->onRewindState();
    }, "", PERMISSION_PAUSEMENU_CLOSED | PERMISSION_FREEPLAY);
}

void SaveStateToolkit::onUnload()
{

}

void SaveStateToolkit::render()
{
    ImGui::Spacing();

    this->renderRewindView();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    this->renderSaveStateView();

    ImGui::Spacing();
}

void SaveStateToolkit::onPhysicsTick()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    if (*this->isRewindActive)
    {
        ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (server.IsNull()) return;

        float currentTime = server.GetSecondsElapsed();

        this->rewindBuffer.empty();
        if (this->rewindBuffer.empty() || currentTime > previousSaveTime + *this->rewindSaveInterval)
        {
            SaveState ss(server);
            this->rewindBuffer.push(ss);
            this->previousSaveTime = currentTime;
        }
    }
}

void SaveStateToolkit::onSaveState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState = SaveState(server);
    this->isStateSaved = true;
}

void SaveStateToolkit::onLoadState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (!this->isStateSaved) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->saveState.applyTo(server);
}

void SaveStateToolkit::onRewindState()
{
    if (!this->plugin->gameWrapper->IsInFreeplay()) return;
    if (this->rewindBuffer.empty()) return;

    ServerWrapper server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    this->rewindBuffer.removeAllButFront();
    SaveState ss = this->rewindBuffer.front();
    ss.applyTo(server);
}

void SaveStateToolkit::setIsRewindActiveCVar(bool active)
{
    CVarWrapper isRewindActiveCVar = this->plugin->cvarManager->getCvar("st_ss_rewindactive");
    if (isRewindActiveCVar.IsNull()) return;

    isRewindActiveCVar.setValue(active);
}

void SaveStateToolkit::onIsRewindActiveCVarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{
    if (!*this->isRewindActive)
    {
        this->rewindBuffer.clear();
    }
}

void SaveStateToolkit::setRewindLengthCVar(float length)
{
    CVarWrapper rewindLengthCVar = this->plugin->cvarManager->getCvar("st_ss_rewindlength");
    if (rewindLengthCVar.IsNull()) return;

    rewindLengthCVar.setValue(length);
}

void SaveStateToolkit::onRewindLengthCvarChanged(const std::string &oldValue, const CVarWrapper &cvar)
{

}

void SaveStateToolkit::setRewindSaveIntervalCVar(float interval)
{
    CVarWrapper rewindSaveIntervalCVar = this->plugin->cvarManager->getCvar("st_ss_rewindsaveinterval");
    if (rewindSaveIntervalCVar.IsNull()) return;

    rewindSaveIntervalCVar.setValue(interval);
}

void SaveStateToolkit::onRewindSaveIntervalChanged(const std::string &oldValue, const CVarWrapper &cvar)
{

}

void SaveStateToolkit::renderRewindView()
{
    if (ImGui::Checkbox("Rewind the game state back a short amount of time", this->isRewindActive.get()))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setIsRewindActiveCVar(*this->isRewindActive);
        });
    }

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();

    ImVec4 color = ImGui::GetStyle().Colors[isInFreeplay ? ImGuiCol_TextDisabled : ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    ImGui::Spacing();

    if (!isInFreeplay || !*this->isRewindActive)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    if (ImGui::Button("Rewind game state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->onRewindState();
        });
    }

    float progress = this->rewindBuffer.progress();
    float frontOffset = this->rewindBuffer.frontOffset();
    ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), std::to_string(frontOffset).c_str());
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("Rewind buffer (in seconds)");

    if (ImGui::SliderFloat("Rewind length (in seconds)", this->rewindLength.get(), 1.0f, 30.0f, "%.3f"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLengthCVar(*this->rewindLength);
        });
    }

    if (ImGui::Button("Default (6.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLengthCVar(6.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Short (2.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLengthCVar(2.0f);
        });
    }
    ImGui::SameLine();
    if (ImGui::Button("Long (12.0)"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->setRewindLengthCVar(12.0f);
        });
    }

//    if (ImGui::SliderFloat("Rewind save interval (in seconds)", this->rewindSaveInterval.get(), 0.001, 0.25, "%.3f"))
//    {
//        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
//            this->setRewindSaveIntervalCVar(*this->rewindSaveInterval);
//        });
//    }

    if (!isInFreeplay || !*this->isRewindActive)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}

void SaveStateToolkit::renderSaveStateView()
{
    ImGui::Text("Save the current game state to be loaded whenever");

    bool isInFreeplay = this->plugin->gameWrapper->IsInFreeplay();
    ImVec4 color = isInFreeplay ? ImGui::GetStyle().Colors[ImGuiCol_TextDisabled] : ImGui::GetStyle().Colors[ImGuiCol_Text];
    ImGui::TextColored(color, "(only works in freeplay and workshop maps)");

    if (!isInFreeplay)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    if (ImGui::Button("Save state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->onSaveState();
        });
    }
    ImGui::SameLine();
    if (isInFreeplay && !this->isStateSaved)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    if (ImGui::Button("Load state"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->onLoadState();
        });
    }
    if (isInFreeplay && !this->isStateSaved)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }

    if (this->isStateSaved)
    {
        this->saveState.render("save state");
    }

    if (!isInFreeplay)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}
