#pragma once
#include <string>
class PersonModel
{
private:
	std::string _FirstName;
	std::string _LastName;
	std::string _PhoneNumber;
	std::string _Email;
public:
	PersonModel(std::string firstName, std::string lastName, std::string email, std::string phoneNumber)
		: _FirstName(firstName), _LastName(lastName), _Email(email), _PhoneNumber(phoneNumber) {
	}
	std::string GetFirstName() const { return _FirstName; }
	std::string GetLastName() const { return _LastName; }
	std::string GetEmail() const { return _Email; }
	std::string GetPhoneNumber() const { return _PhoneNumber; }
	void SetFirstName(const std::string& firstName) { _FirstName = firstName; }
	void SetLastName(const std::string& lastName) { _LastName = lastName; }
	void SetEmail(const std::string& email) { _Email = email; }
	void SetPhoneNumber(const std::string& phoneNumber) { _PhoneNumber = phoneNumber; }
	std::string GetFullName() const { return _FirstName + " " + _LastName; }

	__declspec(property(get = GetFirstName, put = SetFirstName)) std::string FirstName;
	__declspec(property(get = GetLastName, put = SetLastName)) std::string LastName;
	__declspec(property(get = GetEmail, put = SetEmail)) std::string Email;
	__declspec(property(get = GetPhoneNumber, put = SetPhoneNumber)) std::string PhoneNumber;
};