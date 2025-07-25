#include "../headers/data_reader.h"
#include <iostream>
#include <array>
#include <string>
#include "../headers/input_validator_utils.h"
#include "../headers/console_helper.h"
#include "../../constants/Messages/messages.h"

using namespace std;

// Reads a line of text from the user after displaying a prompt
string DataReader::PromptAndReadLine(const string message)
{
    cout << message;
    string stLine;
    getline(cin >> ws, stLine);
    cout << "\n\n";
    return stLine;
}

// Reads an integer from the user, keeps prompting until valid
int DataReader::ReadIntNumber(const string errorMessage)
{
    int number;
    while (!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage;
    }
    return number;
}

// Reads an integer within a specified range
int DataReader::ReadIntNumberBetween(int from, int to, string errorMessage)
{
    int number = ReadIntNumber();

    while (!InputValidatorUtils::IsNumberBetween(number, from, to))
    {
        cout << errorMessage;
        number = ReadIntNumber();
    }
    return number;
}

// Prompts and reads an integer from the user
int DataReader::PromptAndReadIntNumber(const string message, const string errorMessage) {
    cout << message;
    return ReadIntNumber();
}

// Prompts and reads an integer within a range
int DataReader::PromptAndReadIntNumberBetween(const int from, const int to, const string message, const string errorMessage) {
    cout << message;
    return ReadIntNumberBetween(from, to, errorMessage);
}

// Reads a float from the user, keeps prompting until valid
float DataReader::ReadFloatNumber(const string errorMessage)
{
    float number;
    while (!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage;
    }
    return number;
}

// Reads a float within a specified range
float DataReader::ReadFloatNumberBetween(const float from, const float to, string errorMessage)
{
    float number = ReadFloatNumber();

    while (!InputValidatorUtils::IsNumberBetween(number, from, to))
    {
        cout << errorMessage;
        number = ReadFloatNumber();
    }
    return number;
}

// Prompts and reads a float from the user
float DataReader::PromptAndReadFloatNumber(const string message, const string errorMessage) {
    cout << message;
    return ReadFloatNumber();
}

// Prompts and reads a float within a range
float DataReader::PromptAndReadFloatNumberBetween(const float from, const float to, const string message, const string errorMessage) {
    cout << message;
    return ReadFloatNumberBetween(from, to, errorMessage);
}

// Reads a double from the user, keeps prompting until valid
double DataReader::ReadDblNumber(const string errorMessage)
{
    double number;
    while (!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMessage;
    }
    return number;
}

// Reads a double within a specified range
double DataReader::ReadDblNumberBetween(const double from, const double to, string errorMessage)
{
    double number = ReadDblNumber();

    while (!InputValidatorUtils::IsNumberBetween(number, from, to))
    {
        cout << errorMessage;
        number = ReadDblNumber();
    }
    return number;
}

// Prompts and reads a double from the user
double DataReader::PromptAndReadDblNumber(const string message, const string errorMessage) {
    cout << message;
    double number = ReadDblNumber();
    cout << "\n\n";
    return number;
}

// Prompts and reads a double within a range
double DataReader::PromptAndReadDblNumberBetween(const double from, const double to, const string message, const string errorMessage) {
    cout << message;
    return ReadDblNumberBetween(from, to, errorMessage);
}

// Reads a short integer from the user, keeps prompting until valid
short DataReader::ReadShortNumber(const string ErrorMessage)
{
    short Number;
    while (!(cin >> Number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ErrorMessage;
    }
    return Number;
}

// Reads a short integer within a specified range
short DataReader::ReadShortNumberBetween(const short from, const short to, string errorMessage)
{
    short number = ReadShortNumber();

    while (!InputValidatorUtils::IsNumberBetween(number, from, to))
    {
        cout << errorMessage;
        number = ReadShortNumber();
    }
    return number;
}

// Prompts and reads a short integer from the user
short DataReader::PromptAndReadShortNumber(const string message, const string errorMessage) {
    cout << message;
    return ReadShortNumber();
}

// Prompts and reads a short integer within a range
short DataReader::PromptAndReadShortNumberBetween(const short from, const short to, const string message, const string errorMessage) {
    cout << message;
    return ReadShortNumberBetween(from, to, errorMessage);
}

// Prompt repeatedly for a valid phone number until it passes validation, then return it
string DataReader::ReadValidPhoneNumber() {
    string phoneNumber = DataReader::PromptAndReadLine(Messages::kEnterPhone);

    while (!InputValidatorUtils::IsValidPhoneNumber(phoneNumber)) {
        phoneNumber = DataReader::PromptAndReadLine(Messages::kInvalidPhone);
    }
    return phoneNumber;
}

// Prompt user for an account balance >= 100, repeat until valid, then return it
float DataReader::ReadValidAccountBalance() {
    float balance = DataReader::PromptAndReadFloatNumber(Messages::kEnterBalance);

    while (balance < 100) {
        balance = DataReader::PromptAndReadFloatNumber(
            Messages::kInvalidBalance
        );
    }
    return balance;
}

// Prompt repeatedly for a valid PIN code (must be exactly 4 or 6 digits), then return it
string DataReader::ReadValidPinCode() {
    string pinCode = DataReader::PromptAndReadLine(Messages::kEnterPin);

    while (!InputValidatorUtils::IsValidPinCode(pinCode)) {
        pinCode = DataReader::PromptAndReadLine(Messages::kInvalidPin);
    }

    return pinCode;
}

// Prompt repeatedly for a valid name until input passes validation, then return it
string DataReader::ReadValidName(const string& nameType)
{
    string name = DataReader::PromptAndReadLine("Please enter a " + nameType + " Name: ");

    // Loop until name is valid according to InputValidatorUtils
    while (!InputValidatorUtils::IsValidName(name)) {
        name = DataReader::PromptAndReadLine("Invalid Name, Please enter a valid " + nameType + " Name: ");
    }
    return name;
}

// Prompt repeatedly for a valid email until input passes validation, then return it
string DataReader::ReadValidEmail() {
    string email = DataReader::PromptAndReadLine(Messages::kEnterEmail);

    while (!InputValidatorUtils::IsValidEmail(email)) {
        email = DataReader::PromptAndReadLine(Messages::kInvalidEmail);
    }

    return email;
}

// Prompt repeatedly for a valid account number until input passes validation, then return it
string DataReader::ReadAccountNumber(string message)
{
    string accountNumber = DataReader::PromptAndReadLine(message);

    while (!InputValidatorUtils::IsValidAccountNumber(accountNumber)) {
        accountNumber = DataReader::PromptAndReadLine(Messages::kInvalidAccountNumber);
    }
    return accountNumber;
}

// Prompt repeatedly for a valid username until input passes validation, then return it
string DataReader::ReadValidUsername(const string message)
{
    string username = DataReader::PromptAndReadLine(message);
    while (!InputValidatorUtils::IsValidUsername(username)) {
        username = DataReader::PromptAndReadLine(Messages::kInvalidUsername);
    }
    return username;
}

// Prompt repeatedly for a valid password until input passes validation, then return it
string DataReader::ReadValidPassword() {
    string pass = DataReader::PromptAndReadLine(Messages::kEnterPassword);

    while (!InputValidatorUtils::IsValidPassword(pass)) {
        pass = DataReader::PromptAndReadLine(Messages::kInvalidPassword);
    }
    return pass;
}

// Collects permission flags from the user interactively
short DataReader::_CollectPermissionFlags(const std::array<string, 9>& listOfQuestions)
{
    string isAccept = "";
    short permissionsValue = 0;
    for (size_t i = 0; i < listOfQuestions.size(); i++)
    {
        do {
            isAccept = DataReader::PromptAndReadLine(listOfQuestions[i]);
        } while (isAccept.empty() || (toupper(isAccept[0]) != 'Y' && toupper(isAccept[0]) != 'N'));

        if (toupper(isAccept[0]) == 'Y') {
            permissionsValue += static_cast<short>(pow(2, i));
        }

        cout << "\n";
    }
    return permissionsValue;
}

// Reads permissions from the user interactively.
short DataReader::ReadPermissions(const array<string, 9>& listOfQuestions) {
    string giveFullAccess;
    do {
        giveFullAccess = DataReader::PromptAndReadLine(Messages::kPermissionFullAccess);
    } while (toupper(giveFullAccess[0]) != 'Y' && toupper(giveFullAccess[0]) != 'N');

    if (toupper(giveFullAccess[0]) == 'Y') {
        return -1;
    }
    cout << Messages::kPermissionPrompt;
    return _CollectPermissionFlags(listOfQuestions);
}

// Asks the user for confirmation (yes/no)
bool DataReader::Confirm(const string message) {
    return AreYouSure(message);
}

// Prompts the user for a yes/no answer, returns true for yes
bool DataReader::AreYouSure(const string message)
{
    std::string input;

    while (true)
    {
        std::cout << "\n" << message;
        std::cin >> input;
        ConsoleHelper::ClearInputBuffer();

        for (char& c : input)
            c = tolower(c);

        if (input == "y" || input == "yes") {
            cout << "\n";
            return true;
        }
        else if (input == "n" || input == "no")
        {
            cout << "\n";
            return false;
        }
        else
            std::cout << "Invalid input! Please enter 'y', 'n', 'yes', or 'no'.\n";
    }
}

// Prompts and reads a currency rate between 0.1 and 1000
float DataReader::CurrencyRate(std::string message) {
    return PromptAndReadFloatNumberBetween(0.1, 1000, message);
}

// Prompts and reads a 3-letter currency code
string DataReader::CurrencyCode(string message) {
    string currencyCode;
    do
    {
        if (currencyCode.size() != 3)
        {
            currencyCode = PromptAndReadLine(message);
        }
    } while (currencyCode.size() != 3);
    return currencyCode;
}