#include "TestToolkit.h"
#include "../../services/MultiEventHooker.h"

TestToolkit::TestToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{

}

std::string TestToolkit::title()
{
    return "Testing";
}

void TestToolkit::onLoad()
{
    this->plugin->cvarManager->registerNotifier("speedrun_test", [this](const std::vector<std::string> &commands) {
        auto s = this->plugin->gameWrapper->GetMainSequence();

        if (s.memory_address == NULL)
        {
            this->plugin->cvarManager->log("Main sequence is null");
            return;
        }

        std::stringstream ss = this->recursiveList(s);
        std::ofstream out("speedrun_test.txt", std::ios::out);
        out << ss.str();
        out.close();
        //this->plugin->cvarManager->log(ss.str());
    }, "", PERMISSION_PAUSEMENU_CLOSED);

//    MultiEventHooker::getInstance(this->plugin).hookEventPost("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &event) {
//        this->onPhysicsTick();
//    });
//    MultiEventHooker::getInstance(this->plugin).hookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &event) {
//        this->plugin->cvarManager->log("here 1");
//    });
//    MultiEventHooker::getInstance(this->plugin).hookEventPost("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &event) {
//        this->onPhysicsTick();
//    });
//    this->plugin->gameWrapper->HookEventPost("Function TAGame.Car_TA.SetVehicleInput", [this](const std::string &event) {
//        CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
//        ControllerInput input = car.GetInput();
//        input.Roll = 1.0f;
//        LocalControllerInputFix::fix(input);
//        car.eventSetVehicleInput(input);
//    });
//    this->plugin->gameWrapper->HookEventWithCaller<CarWrapper>("Function TAGame.Car_TA.SetVehicleInput", [this](CarWrapper cw, void *params, std::string event) {
//        ((ControllerInput* ) params)->Roll = 1.0f;
//    });
}

void TestToolkit::onUnload()
{

}

void TestToolkit::render()
{

}

void TestToolkit::onPhysicsTick()
{
    CarWrapper car = this->plugin->gameWrapper->GetLocalCar();
    ControllerInput p = car.GetInput();
    p.Roll = 1.0;
    car.eventSetVehicleInput(p);
    if (p.Jumped)
        this->plugin->cvarManager->log("here 333 " + std::to_string(p.Jumped));
}

void TestToolkit::onPhysicsTick(CarWrapper cw, ControllerInput *input, std::string event)
{
    if (input->Jumped)
        this->plugin->cvarManager->log("here 444 " + std::to_string(input->Jumped));
    input->Roll = -1.0f;
}

std::stringstream TestToolkit::recursiveList(SequenceWrapper sequence)
{
    std::stringstream ss;

    if (sequence.memory_address == NULL) return ss;

    auto list = sequence.GetSequenceObjects();
    ss << "Count = " + std::to_string(list.Count()) << "\n";
    for (auto var : list)
    {
        ss << "Object name = " + var.GetObjName().ToString() << "\n";
        if (var.GetObjName().ToString() == "Object")
        {
            SequenceVariableWrapper v(var.memory_address);
            if (v.GetVarName() == "Points")
            {
                int points = v.GetInt();
                this->plugin->cvarManager->log(std::to_string(points));
            }
        }
    }

    auto subs = sequence.GetNestedSequences();
    for (const auto &sub : subs)
    {
        ss << this->recursiveList(sub).str();
    }

    return ss;
}
