#ifndef LOLLMSCIENT_H
#define LOLLMSCIENT_H

#include <iostream>
#include <string>
#include <sio_client.h>
#include <iostream>
#include <string>
#include <thread>
#include <ASCIIColors.h>

class lollmsClient {
public:
    lollmsClient(const std::string& serverUrl);

    // Define event handler types
    using ConnectedEventHandler = std::function<void()>;
    using DisconnectedEventHandler = std::function<void()>;

    using ConnectionFailedHandler = std::function<void()>;
    using ReconnectingHandler = std::function<void(unsigned int reconnectionAttempts, unsigned int delay)>;

    using TextChunkReceivedHandler = std::function<void(std::string)>;
    using FullTextReceivedHandler = std::function<void(std::string)>;

    // Register event handlers
    void onConnected(const ConnectedEventHandler& handler);
    void onDisconnected(const DisconnectedEventHandler& handler);

    void onConnectionFailed(const ConnectionFailedHandler& handler);
    void onReconnecting(const ReconnectingHandler& handler);

    void onChunkReceived(const TextChunkReceivedHandler& handler);
    void onFullTextReceived(const FullTextReceivedHandler& handler);


    void generateText(const std::string& prompt, int n_predicts = 128);

    void cancelGeneration();

    const sio::client& getClient() const;

    void closeConnection();

private:
    sio::client client_;
    bool connected_;

    // Store registered event handlers
    ConnectedEventHandler connectedHandler_;
    DisconnectedEventHandler disconnectedHandler_;    

    ConnectionFailedHandler connectionFailedHandler_;
    ReconnectingHandler reconnectingHandler_;

    TextChunkReceivedHandler textChunkReceivedHandler_;
    FullTextReceivedHandler fullTextReceivedHandler_;

    void setupEventListeners();

};

#endif // LOLLMSCIENT_H
