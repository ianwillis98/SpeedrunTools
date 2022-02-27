#include "LethsEgyptianTombAutoSplitterComponent.h"

LethsEgyptianTombAutoSplitterComponent::LethsEgyptianTombAutoSplitterComponent(NetcodePlugin* plugin)
    : AutoSplitterComponent(plugin),
    ankhs()
{
}

void LethsEgyptianTombAutoSplitterComponent::onEnable()
{
    this->ankhs = this->kismetModel.getIntValue("ankh");
}

void LethsEgyptianTombAutoSplitterComponent::update(const std::string& eventName, bool post, void* params)
{
    if (eventName == "Function TAGame.Car_TA.SetVehicleInput" && post)
    {
        int previousAnkh = this->ankhs;
        this->ankhs = this->kismetModel.getIntValue("ankh");

        auto server = this->plugin->gameWrapper->GetGameEventAsServer();
        if (!server) return;
        auto cars = server.GetCars();
        if (cars.IsNull()) return;

        if (this->segment == 0)
        {
            std::vector<int> pris;
            for (int i = 0; i < cars.Count(); i++) {
                auto car = cars.Get(i);
                if (car.IsNull()) continue;
                auto pri = car.GetPRI();
                if (pri.IsNull()) continue;
                pris.push_back(pri.GetPlayerID());
                if (this->segment == 0 && car.GetLocation().Y >= 5460.0f)
                {
                    this->start(true);
                }
            }
            if (this->segment == 1) {
                this->priFinishedMap.clear();
                for (auto& pri : pris)
                    this->priFinishedMap[pri] = false;
            }
        }
        else if (1 <= this->segment && this->segment <= 6)
        {
            if (this->ankhs >= (previousAnkh + 1) && this->ankhs >= (this->segment + (4 * this->segment)))
                this->split(true);
        }
        else if (this->segment == 7)
        {
            for (int i = 0; i < cars.Count(); i++) {
                auto car = cars.Get(i);
                if (car.IsNull()) continue;
                float x = car.GetLocation().X;
                float y = car.GetLocation().Y;
                if (x > 25480.0f && x < 26710.0f && y > -8080.0f && y < -5920.0f && this->segment == 7)
                {
                    this->split(true);
                    return;
                }
            }
        }
        else if (this->segment == 8)
        {
            for (int i = 0; i < cars.Count(); i++) {
                auto car = cars.Get(i);
                if (car.IsNull()) continue;
                auto pri = car.GetPRI();
                if (pri.IsNull()) continue;
                int id = pri.GetPlayerID();
                if (this->priFinishedMap.find(id) == this->priFinishedMap.end()) continue;
                if (!this->priFinishedMap[id] && car.GetLocation().Z > 10450.0f) {
                    this->priFinishedMap[id] = true;
                }
            }
            for (const auto& elem : this->priFinishedMap) {
                if (!elem.second) return;
            }
            this->split(true);
        }
    }
    if (eventName == "Function TAGame.GameEvent_Soccar_TA.Destroyed" && post)
    {
        this->reset(true);
        this->priFinishedMap.clear();
    }
}

std::string LethsEgyptianTombAutoSplitterComponent::getStartDescription()
{
    return "The timer will start when you cross the barrier at the start.";
}

std::string LethsEgyptianTombAutoSplitterComponent::getSplitDescription()
{
    return "The timer will split every 5 ankhs collected, gaining access to the secret room,\n and once all players complete the true ending (8 splits in total).";
}

std::string LethsEgyptianTombAutoSplitterComponent::getResetDescription()
{
    return "The timer will reset after leaving the map.";
}

std::string LethsEgyptianTombAutoSplitterComponent::getDebugText()
{
    std::stringstream ss;
    ss << "Leth's Egyptian Tomb Auto Splitter (Debug)" << std::endl;
    ss << "ankh = " << this->ankhs << std::endl;
    return ss.str();
}
