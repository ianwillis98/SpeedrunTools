#include "TutorialBasicMapTools.h"

TutorialBasicMapTools::TutorialBasicMapTools(BakkesMod::Plugin::BakkesModPlugin *plugin) : MapToolsBase(plugin)
{

}

void TutorialBasicMapTools::render()
{
    ImGui::Text("Tutorial Basic map tools");
}
