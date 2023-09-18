#include <LollmsClient.h>

using namespace sio;

lollmsClient::lollmsClient(const std::string& serverUrl) : connected_(false) {
    // Set up event listeners
    setupEventListeners();

    std::cout << "Built listeners" << std::endl;
    client_.set_logs_quiet();
    // Connect to the server
    client_.connect(serverUrl);
}
// ****************** Register events ***************************
void lollmsClient::onConnected(const ConnectedEventHandler& handler) {
    connectedHandler_ = handler;
}
void lollmsClient::onDisconnected(const DisconnectedEventHandler& handler) {
    disconnectedHandler_ = handler;
}
void lollmsClient::onConnectionFailed(const ConnectionFailedHandler& handler){
    connectionFailedHandler_ = handler;
}
void lollmsClient::onReconnecting(const ReconnectingHandler& handler){
    reconnectingHandler_ = handler;
}

void lollmsClient::onChunkReceived(const TextChunkReceivedHandler& handler) {
    textChunkReceivedHandler_ = handler;
}
void lollmsClient::onFullTextReceived(const FullTextReceivedHandler& handler) {
    textChunkReceivedHandler_ = handler;
}
// ****************** Methods ***************************
void lollmsClient::generateText(const std::string& prompt, int n_predicts) {
    if (connected_) {
        object_message::ptr om = object_message::create();
        om->get_map()["prompt"] = sio::string_message::create(prompt);
        om->get_map()["n_predicts"] = sio::int_message::create(n_predicts);
        client_.socket()->emit("generate_text", om);
    } else {
        std::cerr << "Not connected to the server. Cannot generate text." << std::endl;
    }
}

void lollmsClient::cancelGeneration() {
    if (connected_) {
        client_.socket()->emit("cancel_generation");
    } else {
        std::cerr << "Not connected to the server. Cannot cancel generation." << std::endl;
    }
}

const sio::client& lollmsClient::getClient() const {
    return client_;
}

void lollmsClient::closeConnection() {
    client_.close();
}


void lollmsClient::setupEventListeners() {
    // Setup event listeners as before
    std::cout<<"Adding open listener"<<std::endl;
    client_.set_open_listener([&]() {
#ifdef __DEBUG__    
        std::cout << "Connected to the LoLLMs server" << std::endl;
#endif
        connected_ = true;
        if (connectedHandler_) {
            connectedHandler_();
        }
    });

    std::cout<<"Adding close listener"<<std::endl;
    client_.set_close_listener([&](sio::client::close_reason const& reason) {
        // Handle disconnected event
#ifdef __DEBUG__    
        std::cout << "Disconnected from the LoLLMs server" << std::endl;
#endif
        connected_ = false;
        if (disconnectedHandler_) {
            disconnectedHandler_();
        }
    });

    std::cout<<"Adding fail listener"<<std::endl;
    client_.set_fail_listener([&]() {
        if(connectionFailedHandler_){
            connectionFailedHandler_();
        }
    });

    std::cout<<"Adding reconnect listener"<<std::endl;
    client_.set_reconnect_listener([&](unsigned int reconnectionAttempts, unsigned int delay) {
        if(reconnectingHandler_){
            reconnectingHandler_(reconnectionAttempts, delay);
        }
    });

    std::cout<<"Adding lollms server listener"<<std::endl;
    // Event handler for receiving generated text chunks
    client_.socket()->on("text_chunk", [&](const sio::event& event) {
        sio::message::ptr message = event.get_message();
        if (message->get_map().find("chunk") != message->get_map().end()) {
            sio::message::ptr chunkMessage = message->get_map()["chunk"];
            if (chunkMessage->get_flag() == sio::message::flag_string) {
                std::string chunk = chunkMessage->get_string();
                if(textChunkReceivedHandler_){
                    textChunkReceivedHandler_(chunk);
                }
            } else {
                std::cerr << "Received 'chunk' data is not a string." << std::endl;
            }
        } else {
            std::cerr << "Received event 'text_chunk' without 'chunk' data." << std::endl;
        }
    });

    // Event handler for receiving generated text
    client_.socket()->on("text_generated", [&](const sio::event& event) {
        ASCIIColors::yellow("\nText generated:");
        sio::message::ptr message = event.get_message();
        if (message->get_map().find("text") != message->get_map().end()) {
            sio::message::ptr chunkMessage = message->get_map()["text"];
            if (chunkMessage->get_flag() == sio::message::flag_string) {
                std::string chunk = chunkMessage->get_string();
                if(fullTextReceivedHandler_){
                    fullTextReceivedHandler_(chunk);
                }
                
            } else {
                std::cerr << "Received 'text' data is not a string." << std::endl;
            }
        } else {
            std::cerr << "Received event 'text_generated' without 'text' data." << std::endl;
        }
    });

    // Event handler for error during text generation
    client_.socket()->on("buzzy", [&](const sio::event& event) {
        const std::string error = event.get_message()->get_string();
        std::cerr << "Server is busy. Wait for your turn. Error: " << error << std::endl;
        // Handle the error or perform any other required actions
        // ...
    });

    // Event handler for generation cancellation
    client_.socket()->on("generation_canceled", [&](const sio::event& event) {
        // Toggle button visibility or perform any other required actions
        std::cout << "Generation canceled" << std::endl;
    });
}

