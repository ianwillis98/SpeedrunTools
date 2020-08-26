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

void LiveSplitClient::connect(const std::string &host, const std::string &port, const std::function<void(int, std::string)> &callback)
{
    if (this->connectionState == ConnectionState::Connecting) return;

    try
    {
        this->connectionState = ConnectionState::Connecting;

        asio::ip::tcp::resolver::query query = asio::ip::tcp::resolver::query(host, port);
        asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(query);
        asio::async_connect(this->socket, endpoint, [this, callback](const asio::error_code &ec, const asio::ip::tcp::resolver::iterator &iterator) {
            callback(ec.value(), ec.message());
            if (ec.value() == 0)
                this->connectionState = ConnectionState::Connected;
        });

        std::thread th([this] {
            if (this->io_context.stopped()) io_context.restart();
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
    this->send("startorsplit");
}

void LiveSplitClient::start()
{
    this->send("starttimer");
}

void LiveSplitClient::pause()
{
    this->send("pause");
}

void LiveSplitClient::resume()
{
    this->send("resume");
}

void LiveSplitClient::reset()
{
    this->send("reset");
}

void LiveSplitClient::split()
{
    this->send("split");
}

void LiveSplitClient::skipSplit()
{
    this->send("skipsplit");
}

void LiveSplitClient::undoSplit()
{
    this->send("unsplit");
}

// TODO: get async_send working
void LiveSplitClient::send(const std::string &message)
{
    if (this->connectionState != ConnectionState::Connected) return;

    try
    {
        this->socket.send(asio::buffer(message + "\r\n"));

//        this->plugin->cvarManager->log("LiveSplitClient: Message sent (" + message + ").");
//        this->plugin->gameWrapper->LogToChatbox("LiveSplitClient: Message sent (" + message + ").", "SPEEDRUNTOOLS");
    }
    catch (const std::exception &e)
    {
        this->connectionState = ConnectionState::NotConnected;

//        this->plugin->cvarManager->log("LiveSplitClient: Error sending message (" + message + "). " + std::string(e.what()));
//        this->plugin->gameWrapper->LogToChatbox("LiveSplitClient: Error sending message (" + message + "). " + std::string(e.what()),
//                                                "SPEEDRUNTOOLS");

        throw;
    }
}
