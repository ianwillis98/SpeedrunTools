#include "../AutoSplitterComponent.h"

class MinigolfAutoSplitterComponent : public AutoSplitterComponent
{
private:
    bool mapStarted;

public:
    explicit MinigolfAutoSplitterComponent(NetcodePlugin* plugin);

    void onEnable() override;
    void update(const std::string& eventName, bool post, void* params) override;

    std::string getStartDescription() override;
    std::string getSplitDescription() override;
    std::string getResetDescription() override;
    std::string getDebugText() override;
};