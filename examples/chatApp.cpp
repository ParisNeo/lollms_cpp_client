#include <iostream>
#include <vector>
#include "lollmsClient.h"

// Define a struct to represent a chat message
struct ChatMessage {
    std::string username;
    std::string message;
};

int main() {
    // Initialize the Lollms client with the server URL
    lollmsClient client("https://localhost:9601");

    // Set up event handlers
    client.onConnected([]() {
        std::cout << "Connected to the Lollms server." << std::endl;
    });

    client.onDisconnected([]() {
        std::cout << "Disconnected from the Lollms server." << std::endl;
    });

    // Connect to the server
    client.getClient().connect();

    // Create a vector to store chat messages
    std::vector<ChatMessage> chatHistory;

    // Handle text chunk received (chat messages)
    client.onChunkReceived([&chatHistory](std::string chunk) {
        // Parse the received message (assuming a format like "username: message")
        size_t colonPos = chunk.find(':');
        if (colonPos != std::string::npos) {
            std::string username = chunk.substr(0, colonPos);
            std::string message = chunk.substr(colonPos + 2); // +2 to skip ': '

            // Create a ChatMessage struct and add it to the chat history
            chatHistory.push_back({username, message});

            // Print the new message
            std::cout << "[" << username << "]: " << message << std::endl;
        }
    });

    // Main chat loop
    while (true) {
        // Read user input
        std::string userInput;
        std::cout << "Enter your message (or type 'exit' to quit): ";
        std::getline(std::cin, userInput);

        // Check if the user wants to exit
        if (userInput == "exit") {
            break;
        }

        // Combine the chat history into a single string as context
        std::string chatContext;
        for (const ChatMessage& message : chatHistory) {
            chatContext += "[" + message.username + "]: " + message.message + "\n";
        }

        // Send the user's message with chat history as context to the server
        client.generateText(chatContext + userInput);

        // You can also display the sent message locally in the chat history
        chatHistory.push_back({"You", userInput});
    }

    // Display the accumulated chat history
    std::cout << "Chat History:" << std::endl;
    for (const ChatMessage& message : chatHistory) {
        std::cout << "[" << message.username << "]: " << message.message << std::endl;
    }

    // Close the connection
    client.closeConnection();

    return 0;
}
