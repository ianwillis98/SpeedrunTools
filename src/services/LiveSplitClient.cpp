#include "LiveSplitClient.h"

LiveSplitClient &LiveSplitClient::getInstance(BakkesMod::Plugin::BakkesModPlugin *plugin)
{
    // assume there will only ever be one plugin instance
    static LiveSplitClient client(plugin);
    return client;
}

LiveSplitClient::LiveSplitClient(BakkesMod::Plugin::BakkesModPlugin *plugin)
        : plugin(plugin), io_context(), socket(io_context), resolver(io_context), connectionState(ConnectionState::NotConnected)
{

}

void
LiveSplitClient::connectAsync(const std::string &host, const std::string &port,
                              const std::function<void(int errorCode, std::string message)> &callback)
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
        throw;
    }
}

ConnectionState LiveSplitClient::getConnectionState()
{
    return this->connectionState;
}

void LiveSplitClient::startOrSplit()
{
    this->sendAsync("startorsplit");
}

void LiveSplitClient::start()
{
    this->sendAsync("starttimer");
}

void LiveSplitClient::pause()
{
    this->sendAsync("pause");
}

void LiveSplitClient::resume()
{
    this->sendAsync("resume");
}

void LiveSplitClient::reset()
{
    this->sendAsync("reset");
}

void LiveSplitClient::split()
{
    this->sendAsync("split");
}

void LiveSplitClient::skipSplit()
{
    this->sendAsync("skipsplit");
}

void LiveSplitClient::undoSplit()
{
    this->sendAsync("unsplit");
}

void LiveSplitClient::sendAsync(const std::string &message)
{
    if (this->connectionState != ConnectionState::Connected)
    {
        throw std::exception("A connection must be established before a message can be send to the LiveSplit Server.");
    }

    try
    {
        auto buffer = asio::buffer(message + "\r\n");
        this->socket.async_send(buffer, [this](const asio::error_code &ec, std::size_t bytes_transferred) {
            bool success = ec.value() == 0;
            this->connectionState = success ? ConnectionState::Connected : ConnectionState::NotConnected;
        });
    }
    catch (const std::exception &e)
    {
        this->connectionState = ConnectionState::NotConnected;
        throw;
    }
}
