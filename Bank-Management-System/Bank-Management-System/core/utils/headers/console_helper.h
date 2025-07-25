#pragma once
#include <string>
// Provides helper methods for console-based UI interactions
class ConsoleHelper
{
public:
    // Displays a message, pauses, then clears the screen
    static void ShowMessageAndPauseThenClear(const std::string & message);

    // Clears any remaining input from the buffer
    static void ClearInputBuffer();

    // Pauses the screen and then clears it
    static void PauseAndClearScreen();

    // Clears the console screen
    static void ClearScreen();
};
