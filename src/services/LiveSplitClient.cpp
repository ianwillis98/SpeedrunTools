#include "LiveSplitClient.h"

LiveSplitClient &LiveSplitClient::getInstance()
{
    static LiveSplitClient instance;
    return instance;
}

LiveSplitClient::LiveSplitClient() : io_context(), socket(io_context), resolver(io_context), connectionState(ConnectionState::NotConnected)
{

}

void LiveSplitClient::connectAsync(const std::string &host, const std::string &port, const ErrorCallback &callback)
{
    if (this->connectionState == ConnectionState::Connecting) return;

    try
    {
        this->connectionState = ConnectionState::Connecting;

        asio::ip::tcp::resolver::query query = asio::ip::tcp::resolver::query(host, port);
        asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(query);
        asio::async_connect(this->socket, endpoint, [this, callback](const asio::error_code &ec, const asio::ip::tcp::resolver::iterator &iterator) {
            this->connectionState = (ec.value() == 0) ? ConnectionState::Connected : ConnectionState::NotConnected;
            callback(ec.value(), ec.message());
        });

        std::thread th([this] {
            if (this->io_context.stopped())
                this->io_context.restart();
            this->io_context.run();
        });
        th.detach();
    }
    catch (const std::exception &e)
    {
        this->connectionState = ConnectionState::NotConnected;
        callback(3591, std::string(e.what()));
    }
}

ConnectionState LiveSplitClient::getConnectionState()
{
    return this->connectionState;
}

void LiveSplitClient::disconnect(const ErrorCallback &callback)
{
    if (this->connectionState == ConnectionState::NotConnected)
    {
        callback(3594, "A connection must be made before disconnecting");
        return;
    }

    this->connectionState = ConnectionState::NotConnected;

    try
    {
        this->socket.shutdown(asio::socket_base::shutdown_both);
        this->socket.close();
        callback(0, "Successfully disconnected from the LiveSplit Server");
    }
    catch (const std::exception &e)
    {
        callback(3593, std::string(e.what()));
    }
}

void LiveSplitClient::startOrSplit(const ErrorCallback &callback)
{
    this->sendAsync("startorsplit", callback);
}

void LiveSplitClient::start(const ErrorCallback &callback)
{
    this->sendAsync("starttimer", callback);
}

void LiveSplitClient::pause(const ErrorCallback &callback)
{
    this->sendAsync("pause", callback);
}

void LiveSplitClient::resume(const ErrorCallback &callback)
{
    this->sendAsync("resume", callback);
}

void LiveSplitClient::reset(const ErrorCallback &callback)
{
    this->sendAsync("reset", callback);
}

void LiveSplitClient::split(const ErrorCallback &callback)
{
    this->sendAsync("split", callback);
}

void LiveSplitClient::skipSplit(const ErrorCallback &callback)
{
    this->sendAsync("skipsplit", callback);
}

void LiveSplitClient::undoSplit(const ErrorCallback &callback)
{
    this->sendAsync("unsplit", callback);
}

void LiveSplitClient::sendAsync(const std::string &message, const ErrorCallback &callback)
{
    if (this->connectionState != ConnectionState::Connected)
    {
        callback(3592, "A connection must be established before a message can be send to the LiveSplit Server");
        return;
    }

    try
    {
        this->socket.async_send(asio::buffer(message + "\r\n"), [this, callback](const asio::error_code &ec, std::size_t bytes_transferred) {
            if (ec.value() != 0)
                this->connectionState = ConnectionState::NotConnected;

            callback(ec.value(), ec.message());
        });

        std::thread th([this] {
            if (this->io_context.stopped())
                this->io_context.restart();
            this->io_context.run();
        });
        th.detach();
    }
    catch (const std::exception &e)
    {
        this->connectionState = ConnectionState::NotConnected;
        this->disconnect([callback, message](const int &errorCode, const std::string &errorMessage) {
            int ec = (errorCode == 0) ? 3592 : errorCode;
            callback(ec, "Error while trying to send a message to the LiveSplit Server (" + message + ")");
        });
    }
}
