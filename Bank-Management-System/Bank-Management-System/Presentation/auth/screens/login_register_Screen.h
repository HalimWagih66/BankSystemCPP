#pragma once
#include "../../base/base_screen.h"
#include "../../../core/types/result_status.h"
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include "../../users/view_model/users_view_model.h"
#include "../../users/helpers/user_ui_helpers.h"
#include "../../../data/models/login_register_model.h"
#include "../../auth/view_model/auth_view_model.h"
class LoginRegisterScreen : protected BaseScreen
{
	static void _PrintLineSeparator() {
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
	}
	static void _PrintLoginRegisterRecordLine(const LoginRegisterModel& LoginRegisterRecord)
	{
		std::cout << std::setw(8) << std::left << "" << "| " << std::setw(35) << std::left << LoginRegisterRecord.DateTime;
		std::cout << "| " << std::setw(20) << std::left << LoginRegisterRecord.Username;
		std::cout << "| " << std::setw(20) << std::left << LoginRegisterRecord.Password;
		std::cout << "| " << std::setw(10) << std::left << LoginRegisterRecord.Permissions;
	}
	static void _PrintLoginRegisterHeaderTable() {
		_PrintLineSeparator();

		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(35) << "Date/Time";
		std::cout << "| " << std::left << std::setw(20) << "UserName";
		std::cout << "| " << std::left << std::setw(20) << "Password";
		std::cout << "| " << std::left << std::setw(10) << "Permissions";

		_PrintLineSeparator();
	}
	static void _PrintLoginRegisterBodyTable(const std::vector<LoginRegisterModel>& vLoginRegisterRecord) {
		if (vLoginRegisterRecord.size() == 0)
			std::cout << "\t\t\t\tNo Logins Available In the System!";
		else
			for (const LoginRegisterModel &Record : vLoginRegisterRecord)
			{
				_PrintLoginRegisterRecordLine(Record);
				std::cout << std::endl;
			}

		_PrintLineSeparator();
	}
	static void _PrintLoginRegisterTable(const std::vector<LoginRegisterModel>& vLoginRegisterRecord) {
		_PrintLoginRegisterHeaderTable();
		_PrintLoginRegisterBodyTable(vLoginRegisterRecord);
	}
public:
	static void ShowLoginRegister(AuthViewModel* authViewModel) {
		if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pLoginRegister)) return;

		std::unique_ptr<std::vector<LoginRegisterModel>> LoginRegisterRecords = std::make_unique<std::vector<LoginRegisterModel>>();
		ResultStatus resultStatus = authViewModel->getRegisterLoginLogs(*LoginRegisterRecords);
		if (resultStatus != ResultStatus::Success)
		{
			_DrawScreenHeader("\tLogin Register List Screen");
			UserUIHelpers::DisplayResultMessage(resultStatus);
			return;
		}
		std::string Title = "\tLogin Register List Screen";
		std::string subTitle = "\t\t(" + to_string(LoginRegisterRecords->size()) + ")" + " Record(s).\n";
		_DrawScreenHeader(Title, subTitle);
		_PrintLoginRegisterTable(*LoginRegisterRecords);
    }
};