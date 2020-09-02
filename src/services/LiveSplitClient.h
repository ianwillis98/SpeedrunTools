#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include<bakkesmod/plugin/bakkesmodplugin.h>
#include "asio.hpp"

enum ConnectionState
{
    NotConnected,
    Connecting,
    Connected
};

using AsyncCallback = std::function<void(int errorCode, std::string message)>;

class LiveSplitClient
{
private:
    asio::io_context io_context;
    asio::ip::tcp::socket socket;
    asio::ip::tcp::resolver resolver;

    ConnectionState connectionState;

    explicit LiveSplitClient();

public:
    static LiveSplitClient &getInstance();

    void connectAsync(const std::string &host, const std::string &port, const AsyncCallback &callback);
    ConnectionState getConnectionState();

    void disconnect();

    void startOrSplit(const AsyncCallback &callback);

    void start(const AsyncCallback &callback);
    void pause(const AsyncCallback &callback);
    void resume(const AsyncCallback &callback);
    void reset(const AsyncCallback &callback);

    void split(const AsyncCallback &callback);
    void skipSplit(const AsyncCallback &callback);
    void undoSplit(const AsyncCallback &callback);

private:
    void sendAsync(const std::string &message, const AsyncCallback &callback);
};
