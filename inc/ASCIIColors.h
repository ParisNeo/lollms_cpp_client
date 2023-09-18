#ifndef ASCIIColors_H
#define ASCIIColors_H

#include <iostream>
#include <string>

class ASCIIColors {
public:
    // Color codes
    static const std::string RESET;
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;

    // Print text in the specified color
    static void printColoredText(const std::string& text, const std::string& color, bool newLine = true, bool flush = true);

    // Print text in a specific color with or without a newline, and optionally flush
    static void red(const std::string& text, bool newLine = true, bool flush = true);
    static void green(const std::string& text, bool newLine = true, bool flush = true);
    static void yellow(const std::string& text, bool newLine = true, bool flush = true);
    static void blue(const std::string& text, bool newLine = true, bool flush = true);
    static void magenta(const std::string& text, bool newLine = true, bool flush = true);
    static void cyan(const std::string& text, bool newLine = true, bool flush = true);
    static void white(const std::string& text, bool newLine = true, bool flush = true);
};

#endif // ASCIIColors_H
