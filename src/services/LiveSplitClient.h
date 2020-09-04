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

using ErrorCallback = std::function<void(int errorCode, std::string message)>;

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

    void connectAsync(const std::string &host, const std::string &port, const ErrorCallback &callback);
    ConnectionState getConnectionState();

    void disconnect(const ErrorCallback &callback);

    void startOrSplit(const ErrorCallback &callback);

    void start(const ErrorCallback &callback);
    void pause(const ErrorCallback &callback);
    void resume(const ErrorCallback &callback);
    void reset(const ErrorCallback &callback);

    void split(const ErrorCallback &callback);
    void skipSplit(const ErrorCallback &callback);
    void undoSplit(const ErrorCallback &callback);

private:
    void sendAsync(const std::string &message, const ErrorCallback &callback);
};
