#include "../headers/input_validator_utils.h"
#include "../headers/string_utils.h"
#include <regex>
using namespace std;

// Checks if the password is valid based on length and character composition:
// - Length must be between 8 and 16 characters
// - Must contain both lowercase and uppercase letters
// - Must contain at least one special character
// - Must contain at least one digit
bool InputValidatorUtils::IsValidPassword(const string& password)
{
	if (password.size() < 8 || password.size() > 16) return false;
	if (!(StringUtils::HasLowerCase(password) && StringUtils::HasUpperCase(password))) return false;
	if (!StringUtils::HasSpecialCharacter(password)) return false;
	if (!StringUtils::HasNumber(password)) return false;

	return true;
}

// Checks if the username is valid based on:
// - Length between 4 and 20 characters
// - Starts with an alphabetic character
// - Contains no spaces
// - Contains only alphabetic characters, possibly with one dot or underscore
bool InputValidatorUtils::IsValidUsername(const string& Username)
{
	if (Username.size() < 4 || Username.size() > 20) return false;
	if (!isalpha(Username[0])) return false;
	if (StringUtils::HasSpace(Username)) return false;
	if (!StringUtils::IsAlphaNameWithOneDotOrUnderscore(Username)) return false;

	return true;
}

// Validates both username and password of a UserInfo object.
bool InputValidatorUtils::IsValidUsernameAndPassword(const string& Username, const string& Password)
{
	// Returns true only if both username and password are valid
	return (InputValidatorUtils::IsValidPassword(Password) && InputValidatorUtils::IsValidUsername(Username));
}

// Checks if a PIN code is valid based on:
// - Length must be either 4 or 6 digits
// - Must consist only of digits
bool InputValidatorUtils::IsValidPinCode(const string& PinCode)
{
	if (PinCode.length() != 4 && PinCode.length() != 6) {
		return false;
	}
	if (!StringUtils::IsAllDigits(PinCode))
	{
		return false;
	}
	return true;
}

// Checks if a name is valid (length and only alphabetic characters)
bool InputValidatorUtils::IsValidName(const string& Name) {
	return (Name.length() >= 3 && Name.length() <= 18) && StringUtils::IsAlphaOnly(Name);
}

// Checks if a phone number is valid (Egyptian format)
bool InputValidatorUtils::IsValidPhoneNumber(const string& phoneNumber)
{
	// Must be exactly 11 characters
	if (phoneNumber.size() != 11)
		return false;

	// Must contain only digits
	if (!StringUtils::IsAllDigits(phoneNumber))
		return false;

	// Must start with "01"
	if (!(phoneNumber[0] == '0' && phoneNumber[1] == '1'))
		return false;

	// Third digit must be one of the valid operator codes: 0, 1, 2, or 5
	if (!(phoneNumber[2] == '0' || phoneNumber[2] == '1' ||
		phoneNumber[2] == '2' || phoneNumber[2] == '5'))
		return false;

	return true; // All checks passed
}

// Checks if an email is valid (must be from allowed domains)
bool InputValidatorUtils::IsValidEmail(const string& Email)
{
	const regex pattern(R"(^[A-Za-z0-9._%+-]+@(gmail\.com|yahoo\.com|hotmail\.com|outlook\.com)$)");
	return regex_match(Email, pattern);
}

// Checks if an account number is valid (10 digits)
bool InputValidatorUtils::IsValidAccountNumber(const string& AccountNumber)
{
	return (AccountNumber.length() == 10 && StringUtils::IsAllDigits(AccountNumber));
}

// Checks if an integer is within a specified range
bool InputValidatorUtils::IsNumberBetween(int Number, int From, int To)
{
	return (Number >= From && Number <= To);
}

// Checks if a short integer is within a specified range
bool InputValidatorUtils::IsNumberBetween(short Number, short From, short To)
{
	return (Number >= From && Number <= To);
}

// Checks if a float is within a specified range
bool InputValidatorUtils::IsNumberBetween(float Number, float From, float To)
{
	return (Number >= From && Number <= To);
}

// Checks if a double is within a specified range
bool InputValidatorUtils::IsNumberBetween(double Number, double From, double To)
{
	return (Number >= From && Number <= To);
}