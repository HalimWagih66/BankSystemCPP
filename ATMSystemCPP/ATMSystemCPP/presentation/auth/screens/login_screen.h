#pragma once
#include "../../base/base_screen.h"
#include <string>
#include <iomanip>
#include "../../../core/utils/headers/data_reader.h"
#include "../../../core/types/result_status.h"
#include "../view_model/auth_view_model.h"
#include "../../../core/utils/headers/console_helper.h"
using namespace std;
class LoginScreen : protected BaseScreen
{
	static void ReadAccountNumberAndPinCode(string& accountNumber, string& pinCode) {
		accountNumber = DataReader::ReadAccountNumber();
		cout << "\n\n";
		pinCode = DataReader::ReadValidPinCode();
	}
	static void _GoToMainScreen() {
		cout <<"You have successfully logged in. Press any key to enter the main menu...\n";
		system("pause>0");
	}
public:
	static ResultStatus ShowLogin(AuthViewModel *loginViewModel) {
		ConsoleHelper::ClearScreen();
		_DrawScreenHeader("\t   Login Screen");
		string accountNumber;
		string pinCode;
		ReadAccountNumberAndPinCode(accountNumber,pinCode);
		ResultStatus resultStatusAuth = loginViewModel->login(accountNumber,pinCode);
		if (resultStatusAuth == ResultStatus::Success)
		{
			_GoToMainScreen();
			return ResultStatus::Success;
		}
		else {
			return resultStatusAuth;
		}
	}
};