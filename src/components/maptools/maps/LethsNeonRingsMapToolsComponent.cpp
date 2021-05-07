#include "LethsNeonRingsMapToolsComponent.h"

LethsNeonRingsMapToolsComponent::LethsNeonRingsMapToolsComponent(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : PluginComponentBase(plugin),
          autoSplitterComponent(plugin)
{

}

void LethsNeonRingsMapToolsComponent::render()
{
    ImGui::Text("MAP TOOLS");
    ImGuiExtensions::BigSpacing();

    ImGuiExtensions::PushDisabledStyle();
    if (ImGui::Button("Load Map (Not Possible Until Map is Officially Released)"))
    {

    }
    ImGuiExtensions::PopDisabledStyle();
    ImGui::Spacing();

    if (ImGui::Button("Reset"))
    {
        this->plugin->gameWrapper->Execute([this](GameWrapper *gw) {
            this->resetMap();
        });
    }
    ImGui::Spacing();

    for (int i = 1; i <= 20; i++)
    {
        std::string label = "Level " + std::to_string(i);
        if (ImGui::Button(label.c_str()))
        {
            this->plugin->gameWrapper->Execute([this, i](GameWrapper *gw) {
                this->level(i);
            });
        }
        if (i % 5 != 0) ImGui::SameLine();
    }

    ImGuiExtensions::BigSeparator();

    ImGui::Text("AUTO SPLITTER");
    ImGuiExtensions::BigSpacing();
    this->autoSplitterComponent.render();
}

void LethsNeonRingsMapToolsComponent::onEvent(const std::string &eventName, bool post, void *params)
{
    this->autoSplitterComponent.onEvent(eventName, post, params);
}

void LethsNeonRingsMapToolsComponent::resetMap()
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto allVars = sequence.GetAllSequenceVariables(false);

    auto level = allVars.find("Level");
    if (level == allVars.end()) return;
    level->second.SetInt(20);

    auto timing = allVars.find("Timing");
    if (timing == allVars.end()) return;
    timing->second.SetBool(true);

    auto normalMode = allVars.find("NormalMode");
    if (normalMode == allVars.end()) return;
    normalMode->second.SetBool(true);

    auto car = this->plugin->gameWrapper->GetLocalCar();
    if (car.IsNull()) return;

    car.SetLocation(Vector(23000, -66500, 57000));
    car.SetVelocity(Vector(0, -2000, -750));
    car.SetRotation(Rotator(0, -16000, 0));
    car.SetAngularVelocity(Vector(0, 0, 0), false);
    // level 20
    // timing true
    // normal true
    // loc 23000 -66500 57000
    // vel 0 -2000 -750
    // rot 0 -16000 0


    // loc 0 891 482
    // vel 0 0 0
    // rot 0 -16400 0
}

void LethsNeonRingsMapToolsComponent::level(int level)
{
    auto sequence = this->plugin->gameWrapper->GetMainSequence();
    if (sequence.memory_address == NULL) return;

    auto allVars = sequence.GetAllSequenceVariables(false);

    auto levelVar = allVars.find("Level");
    if (levelVar == allVars.end()) return;
    levelVar->second.SetInt(level);

    auto server = this->plugin->gameWrapper->GetGameEventAsServer();
    if (server.IsNull()) return;

    server.ResetPlayers();
}
