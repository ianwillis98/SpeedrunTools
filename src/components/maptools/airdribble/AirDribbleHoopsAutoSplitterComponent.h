#include "../AutoSplitterComponent.h"

class AirDribbleHoopsAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool timer;
    int level;

public:
    explicit AirDribbleHoopsAutoSplitterComponent(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void onEnable() override;
    void update(const std::string &eventName, bool post, void *params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};
