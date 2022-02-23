#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "utils/NetcodeManager.h"
#include <memory>

class NetcodePlugin : public BakkesMod::Plugin::BakkesModPlugin
{
protected:
	std::shared_ptr<NetcodeManager> Netcode;

public:
	virtual void NotifyPlayers(std::string message) = 0;
};
