#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "asio.hpp"

class LiveSplitClient
{
public:
    using ResultCallback = std::function<void(bool success, std::string message)>;

private:
    asio::io_context io_context;
    asio::ip::tcp::socket socket;
    asio::ip::tcp::resolver resolver;

    bool connected;
    bool connecting;

    LiveSplitClient();

public:
    static LiveSplitClient &getInstance();

    void connect(const std::string &host, const std::string &port, const ResultCallback &callback);
    void disconnect(const ResultCallback &callback);
    bool isConnected() const;
    bool isConnecting() const;

    void startOrSplit(const ResultCallback &callback);

    void start(const ResultCallback &callback);
    void pause(const ResultCallback &callback);
    void resume(const ResultCallback &callback);
    void reset(const ResultCallback &callback);

    void split(const ResultCallback &callback);
    void skipSplit(const ResultCallback &callback);
    void undoSplit(const ResultCallback &callback);

private:
    void send(const std::string &message, const ResultCallback &callback);
};
