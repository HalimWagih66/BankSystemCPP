#pragma once
#include "../../base/base_screen.h"
#include <string>
#include <iomanip>
#include "../../../core/utils/headers/data_reader.h"
#include "../../../core/types/result_status.h"
#include "../view_model/auth_view_model.h"
using namespace std;
class LoginScreen : protected BaseScreen
{
	static void ReadUsernameAndPassword(string& Username, string& Password) {
		Username = DataReader::ReadValidUsername();
		cout << "\n\n";
		Password = DataReader::ReadValidPassword();
	}
	static void _GoToMainScreen() {
		cout <<"You have successfully logged in. Press any key to enter the main menu...\n";
		system("pause>0");
	}
public:
	static ResultStatus ShowLogin(AuthViewModel *loginViewModel) {
		ConsoleHelper::ClearScreen();
		_DrawScreenHeader("\t   Login Screen");
		string Username;
		string Password;
		ReadUsernameAndPassword(Username,Password);
		ResultStatus resultStatusAuth = loginViewModel->login(Username,Password);
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