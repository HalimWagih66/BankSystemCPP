#include <iostream>
#include "../headers/console_helper.h"
#include <string>
using namespace std;

// Displays a message, waits for user to press a key, then clears the screen
void ConsoleHelper::ShowMessageAndPauseThenClear(const string& message)
{
	cout << message;
	system("pause>nul");
	ClearScreen();
}

// Clears any remaining input in the input buffer
void ConsoleHelper::ClearInputBuffer()
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// Pauses for user input and then clears the screen
void ConsoleHelper::PauseAndClearScreen()
{
	system("pause>nul");
	ClearScreen();
}

// Clears the console screen
void ConsoleHelper::ClearScreen()
{
	system("cls");
}