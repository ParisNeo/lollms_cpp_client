# LollmsClientLib

[![GitHub license](https://img.shields.io/github/license/ParisNeo/lollms_cpp_client)](https://github.com/ParisNeo/lollms_cpp_client/blob/master/LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/ParisNeo/lollms_cpp_client)](https://github.com/ParisNeo/lollms_cpp_client/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/ParisNeo/lollms_cpp_client)](https://github.com/ParisNeo/lollms_cpp_client/issues)
![GitHub last commit](https://img.shields.io/github/last-commit/ParisNeo/lollms_cpp_client)

## Overview

The LollmsClientLib is a C++ library for connecting to the Lollms (Lord Of Large Language ModelS) text generation service. It allows you to interact with the Lollms server, send prompts for text generation, and receive generated text in real-time.

## Features

- Connect to the Lollms server and manage the connection state.
- Send prompts for text generation.
- Receive generated text in chunks or as a complete text.
- Handle connection events like successful connection, disconnection, and reconnection attempts.
- Gracefully cancel text generation requests.
- Handle errors and busy server states.

## Installation

To use the LollmsClientLib library, follow these steps:

1. Clone this repository to your local machine:

   ```shell
   git clone https://github.com/ParisNeo/lollms_cpp_client.git
   ```

2. Build and install the `socket.io-client-cpp` dependency:

   ```shell
   cd lollms_cpp_client
   mkdir build && cd build
   cmake ..
   make
   sudo make install
   ```

3. Build your project, linking it with the LollmsClientLib library and the `sioclient` dependency.

## Usage

Here's a detailed example of how to use the LollmsClientLib library in your C++ project:

```cpp
#include <iostream>
#include "lollmsClient.h"

int main() {
    // Start a lollms server (default address is localhost:9601)
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

    // Handle text chunk received
    client.onChunkReceived([](std::string chunk) {
        std::cout << "Received text chunk: " << chunk << std::endl;
    });

    // Handle full text received
    client.onFullTextReceived([](std::string text) {
        std::cout << "Received full generated text: " << text << std::endl;
    });

    // Generate text
    client.generateText("Once upon a time, in a land far, far away", 128);

    // Wait for user input to cancel text generation
    std::cout << "Press Enter to cancel text generation..." << std::endl;
    std::cin.get();

    // Cancel text generation
    client.cancelGeneration();

    // Close the connection
    client.closeConnection();

    return 0;
}
```

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.
```
