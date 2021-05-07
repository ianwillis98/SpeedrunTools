#include "LiveSplitClient.h"

LiveSplitClient &LiveSplitClient::getInstance()
{
    static LiveSplitClient instance;
    return instance;
}

LiveSplitClient::LiveSplitClient()
        : io_context(),
          socket(io_context),
          resolver(io_context),
          connected(false),
          connecting(false)
{

}

void LiveSplitClient::connect(const std::string &host, const std::string &port, const ResultCallback &callback)
{
    if (this->isConnecting())
    {
        callback(false, "Already attempting to establish a connection with the LiveSplit Server...");
        return;
    }
    if (this->isConnected())
    {
        callback(false, "A connection has already been established with the LiveSplit Server.");
        return;
    }

    this->connecting = true;

    try
    {
        asio::ip::tcp::resolver::query query = asio::ip::tcp::resolver::query(host, port);
        asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(query);
        asio::async_connect(this->socket, endpoint,
                            [this, port, callback](const asio::error_code &ec, const asio::ip::tcp::resolver::iterator &iterator) {
                                this->connected = (ec.value() == 0);
                                this->connecting = false;
                                callback((ec.value() == 0),
                                         (ec.value() == 0) ? "Successfully connected to the LiveSplit Server."
                                                           : "Unable to connect to the LiveSplit Server: \"" + ec.message() + "\"." +
                                                             "\nMake sure the LiveSplit Server is running and open on port " + port + ".");
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
        this->connected = false;
        this->connecting = false;
        callback(false, "Error while connecting to the LiveSplit Server: \"" + std::string(e.what()) + "\".");
    }
}

void LiveSplitClient::disconnect(const ResultCallback &callback)
{
    if (this->isConnecting())
    {
        callback(false, "Cannot disconnect from the LiveSplit Server while attempting to establish a connection...");
        return;
    }
    if (!this->isConnected())
    {
        callback(false, "A connection must be established with the LiveSplit Server before disconnecting.");
        return;
    }

    this->connected = false;

    try
    {
        this->socket.shutdown(asio::socket_base::shutdown_both);
        this->socket.close();
        callback(true, "Successfully disconnected from the LiveSplit Server.");
    }
    catch (const std::exception &e)
    {
        callback(false, "Error while disconnecting from the LiveSplit Server: \"" + std::string(e.what()) + "\".");
    }
}

bool LiveSplitClient::isConnected() const
{
    return this->connected;
}

bool LiveSplitClient::isConnecting() const
{
    return this->connecting;
}

void LiveSplitClient::startOrSplit(const ResultCallback &callback)
{
    this->sendAsync("startorsplit", callback);
}

void LiveSplitClient::start(const ResultCallback &callback)
{
    this->sendAsync("starttimer", callback);
}

void LiveSplitClient::pause(const ResultCallback &callback)
{
    this->sendAsync("pause", callback);
}

void LiveSplitClient::resume(const ResultCallback &callback)
{
    this->sendAsync("resume", callback);
}

void LiveSplitClient::reset(const ResultCallback &callback)
{
    this->sendAsync("reset", callback);
}

void LiveSplitClient::split(const ResultCallback &callback)
{
    this->sendAsync("split", callback);
}

void LiveSplitClient::skipSplit(const ResultCallback &callback)
{
    this->sendAsync("skipsplit", callback);
}

void LiveSplitClient::undoSplit(const ResultCallback &callback)
{
    this->sendAsync("unsplit", callback);
}

void LiveSplitClient::sendAsync(const std::string &message, const ResultCallback &callback)
{
    if (this->isConnecting())
    {
        callback(false, "A message cannot be sent to the LiveSplit Server while attempting to establish a connection...");
        return;
    }
    if (!this->isConnected())
    {
        callback(false, "A connection must be established to the LiveSplit Server before a message can be sent.");
        return;
    }

    try
    {
        this->socket.async_send(asio::buffer(message + "\r\n"), [this, message, callback](const asio::error_code &ec, std::size_t bytes_transferred) {
            this->connected = (ec.value() == 0);
            callback((ec.value() == 0), (ec.value() == 0) ? "'" + message + "' message was successfully sent to the LiveSplit Server." :
                                        "Error while sending message '" + message + "' to the LiveSplit Server: \"" + ec.message() + "\".");
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
        this->connected = false;
        this->disconnect([message, callback](const int &errorCode, const std::string &errorMessage) {
            callback(false, "Error while trying to send a message to the LiveSplit Server: \"" + message + "\".");
        });
    }
}
