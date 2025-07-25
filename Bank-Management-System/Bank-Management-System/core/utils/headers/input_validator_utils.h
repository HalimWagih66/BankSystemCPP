#pragma once
#include <string>

class InputValidatorUtils
{
public:
    // Checks if the password meets defined validation rules
    static bool IsValidPassword(const std::string& password);

    // Validates the format of a username (letters, length, etc.)
    static bool IsValidUsername(const std::string& Username);

    // Validates both username and password together
    static bool IsValidUsernameAndPassword(const std::string& Username, const std::string& password);

    // Validates PIN code format (length, digits only)
    static bool IsValidPinCode(const std::string& pinCode);

    // Validates name format (only letters and spaces, possibly other rules)
    static bool IsValidName(const std::string& name);

    // Validates phone number format (digits, length, etc.)
    static bool IsValidPhoneNumber(const std::string& phoneNumber);

    // Validates email format using a basic pattern
    static bool IsValidEmail(const std::string& email);

    // Validates account number format (usually digits and length)
    static bool IsValidAccountNumber(const std::string& accountNumber);

    // Checks if an integer is within a specified range
    static bool IsNumberBetween(int number, int from, int to);

    // Checks if a short integer is within a specified range
    static bool IsNumberBetween(short number, short from, short to);

    // Checks if a float number is within a specified range
    static bool IsNumberBetween(float number, float from, float to);

    // Checks if a double number is within a specified range
    static bool IsNumberBetween(double number, double from, double to);
};
