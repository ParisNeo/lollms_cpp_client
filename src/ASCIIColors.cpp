#include "ASCIIColors.h"

// Define the ANSI escape codes
const std::string ASCIIColors::RESET = "\033[0m";
const std::string ASCIIColors::BLACK = "\033[30m";
const std::string ASCIIColors::RED = "\033[31m";
const std::string ASCIIColors::GREEN = "\033[32m";
const std::string ASCIIColors::YELLOW = "\033[33m";
const std::string ASCIIColors::BLUE = "\033[34m";
const std::string ASCIIColors::MAGENTA = "\033[35m";
const std::string ASCIIColors::CYAN = "\033[36m";
const std::string ASCIIColors::WHITE = "\033[37m";

// Print text in the specified color
void ASCIIColors::printColoredText(const std::string& text, const std::string& color, bool newLine, bool flush) {
    std::cout << color << text << RESET;
    if (newLine)
        std::cout << std::endl;
    else
        if (flush)
            std::cout.flush();
}

// Print text in a specific color with or without a newline, and optionally flush
void ASCIIColors::red(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, RED, newLine, flush);
}

void ASCIIColors::green(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, GREEN, newLine, flush);
}

void ASCIIColors::yellow(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, YELLOW, newLine, flush);
}

void ASCIIColors::blue(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, BLUE, newLine, flush);
}

void ASCIIColors::magenta(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, MAGENTA, newLine, flush);
}

void ASCIIColors::cyan(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, CYAN, newLine, flush);
}

void ASCIIColors::white(const std::string& text, bool newLine, bool flush) {
    printColoredText(text, WHITE, newLine, flush);
}
