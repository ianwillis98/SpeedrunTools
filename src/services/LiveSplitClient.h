#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <bakkesmod/plugin/bakkesmodplugin.h>
#include "asio.hpp"

enum ConnectionState
{
    NotConnected,
    Connecting,
    Connected
};

class LiveSplitClient
{
private:
    BakkesMod::Plugin::BakkesModPlugin *plugin;

    asio::io_context io_context;
    asio::ip::tcp::socket socket;
    asio::ip::tcp::resolver resolver;

    ConnectionState connectionState;

    explicit LiveSplitClient(BakkesMod::Plugin::BakkesModPlugin *plugin);

public:
    static LiveSplitClient &getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin);

    void connect(const std::string &host, const std::string &port, const std::function<void(int, std::string)> &);
    ConnectionState getConnectionState();

    void startOrSplit();

    void start();
    void pause();
    void resume();
    void reset();

    void split();
    void skipSplit();
    void undoSplit();

private:
    void send(const std::string &message);
};
