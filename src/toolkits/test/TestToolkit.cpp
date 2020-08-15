//
// Created by Ian on 8/15/2020.
//

#include "TestToolkit.h"

TestToolkit::TestToolkit(BakkesMod::Plugin::BakkesModPlugin *plugin) : PluginToolkit(plugin)
{
    this->gravity = std::make_shared<float>();
}

std::string TestToolkit::title()
{
    return "Test Toolkit";
}

void TestToolkit::onLoad()
{

}

void TestToolkit::onUnload()
{

}

void TestToolkit::render()
{

}

void TestToolkit::setGameGravity(float g)
{

}
