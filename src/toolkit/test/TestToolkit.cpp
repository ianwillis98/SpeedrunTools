#include "TestToolkit.h"

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
}

void TestToolkit::onUnload()
{

}

void TestToolkit::render()
{

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
        if (var.GetObjName().ToString() == "Int")
        {
            SequenceVariableWrapper v(var.memory_address);
            if (v.GetVarName() != "None" && v.GetVarName() != "QWordProperty")
                this->plugin->cvarManager->log(v.GetVarName());
        }
    }

    auto subs = sequence.GetNestedSequences();
    for (const auto &sub : subs)
    {
        //ss << this->recursiveList(sub).str();
    }

    return ss;
}
