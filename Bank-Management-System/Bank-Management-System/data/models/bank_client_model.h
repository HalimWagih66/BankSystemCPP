#pragma once
#include "person_model.h"
#include <string>
#include <iostream>
#include "../../core/utils/headers/data_reader.h"
class BankClientModel : public PersonModel {
private:
	float _AccountBalance;
	std::string _PinCode;
	bool _MarkedForDelete = false;
	std::string _AccountNumber;

public:
	BankClientModel() : PersonModel("", "", "", "") {
		_AccountBalance = 0;
		_PinCode = "";
		_MarkedForDelete = false;
		_AccountNumber = "";
	};
	BankClientModel(const std::string FirstName, const std::string LastName, const std::string Email, const std::string Phone, const std::string AccountNumber, const std::string PinCode, const double AccountBalance) :PersonModel(FirstName, LastName, Email, Phone), _AccountNumber(AccountNumber), _PinCode(PinCode), _AccountBalance(AccountBalance) {}

	std::string GetFullName() const {
		return FirstName + " " + LastName;
	}
	std::string GetAccountNumber() const { return _AccountNumber; }
	void SetAccountNumber(const std::string& AccountNumber) { _AccountNumber = AccountNumber; }
	__declspec(property(get = GetAccountNumber, put = SetAccountNumber)) std::string accountNumber;

	void SetPinCode(const std::string& PinCode) { _PinCode = PinCode; }
	std::string GetPinCode() const { return _PinCode; }
	__declspec(property(get = GetPinCode, put = SetPinCode)) std::string PinCode;


	void SetAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }
	float GetAccountBalance() const { return _AccountBalance; }
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float accountBalance;

	bool GetMarkedForDelete()const {
		return _MarkedForDelete;
	}
	void SetMarkedForDelete(bool MarkedForDelete) {
		_MarkedForDelete = MarkedForDelete;
	}


	void PrintInfo()
	{
		std::cout << "\nClient Card:";
		std::cout << "\n___________________";
		std::cout << "\nFirstName   : " << FirstName << "\n";
		std::cout << "\nLastName    : " << LastName << "\n";
		std::cout << "\nFull Name   : " << GetFullName() << "\n";
		std::cout << "\nEmail       : " << Email << "\n";
		std::cout << "\nPhone       : " << PhoneNumber << "\n";
		std::cout << "\nAcc. Number : " << accountNumber << "\n";
		std::cout << "\nPassword    : " << PinCode << "\n";
		std::cout << "\nBalance     : " << accountBalance << "\n";
		std::cout << "\n___________________\n";

	}
	void ReadInfo() {
		FirstName = DataReader::ReadValidName("First");
		LastName = DataReader::ReadValidName("Last");
		Email = DataReader::ReadValidEmail();
		PhoneNumber = DataReader::ReadValidPhoneNumber();
		PinCode = DataReader::ReadValidPinCode();
		accountBalance = DataReader::ReadValidAccountBalance();
	}
};