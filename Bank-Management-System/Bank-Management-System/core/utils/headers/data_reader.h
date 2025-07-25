#pragma once
#include <string>
#include "../../constants/Messages/messages.h"
#include <array>
class DataReader
{
private:
    // Helper to collect permission flags from user input
    static short _CollectPermissionFlags(const std::array<std::string, 9>& listOfQuestions);


public:

    // Prompts the user with a message and reads a full line of input
    static std::string PromptAndReadLine(const std::string Message);

    // Read integer with optional error message
    static int ReadIntNumber(const std::string ErrorMessage = Messages::kInvalidNumber);

    // Read integer within a specific range
    static int ReadIntNumberBetween(const int From, const int To, const std::string ErrorMessage = Messages::kNumberOutOfRange);

    // Prompt and read integer input
    static int PromptAndReadIntNumber(const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kInvalidNumber);

    // Prompt and read integer input within range
    static int PromptAndReadIntNumberBetween(const int From, const int To, const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kNumberOutOfRange);

    // Same structure for float inputs
    static float ReadFloatNumber(const std::string ErrorMessage = Messages::kInvalidNumber);
    static float ReadFloatNumberBetween(const float From, const float To, const std::string ErrorMessage = Messages::kNumberOutOfRange);
    static float PromptAndReadFloatNumber(const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kInvalidNumber);
    static float PromptAndReadFloatNumberBetween(const float From, const float To, const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kNumberOutOfRange);

    // Same structure for double inputs
    static double ReadDblNumber(const std::string ErrorMessage = Messages::kInvalidNumber);
    static double ReadDblNumberBetween(double From, double To, const std::string ErrorMessage = Messages::kNumberOutOfRange);
    static double PromptAndReadDblNumber(const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kInvalidNumber);
    static double PromptAndReadDblNumberBetween(const double From, const double To, const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kNumberOutOfRange);

    // Same structure for short inputs
    static short ReadShortNumber(const std::string ErrorMessage = Messages::kInvalidNumber);
    static short ReadShortNumberBetween(const short From, const short To, const std::string ErrorMessage = Messages::kNumberOutOfRange);
    static short PromptAndReadShortNumber(const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kInvalidNumber);
    static short PromptAndReadShortNumberBetween(const short From, const short To, const std::string Message = Messages::kPromptEnterNumber, const std::string ErrorMessage = Messages::kNumberOutOfRange);

    // Valid input readers
    static std::string ReadValidPhoneNumber();
    static float ReadValidAccountBalance();
    static std::string ReadValidPinCode();
    static std::string ReadValidName(const std::string& nameType);
    static std::string ReadValidEmail();
    static std::string ReadAccountNumber(std::string Message = "Please enter an account number: ");
    static std::string ReadValidUsername(const std::string Message = "Please enter a Username: ");
    static std::string ReadValidPassword();

    // Collect multiple permission values
    static short ReadPermissions(const std::array<std::string, 9>& listOfQuestions);

    // Prompt user for confirmation with a message
    static bool AreYouSure(const std::string message);
    static bool Confirm(const std::string message);

    // Prompts the user to enter a currency exchange rate (float), with validation
    static float CurrencyRate(std::string message = "Please enter new currency rate : ");
    // Prompts the user to enter a currency code (must be 3 characters), with validation
    static std::string CurrencyCode(std::string message = "Please enter currency code has contain 3 characters : ");
};
