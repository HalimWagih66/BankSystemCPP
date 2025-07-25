#pragma once
#include "../../base/base_screen.h"
#include "../../../data/data_source/users/interface/interface_user_data_source.h"
#include "../../Users/helpers/user_ui_helpers.h"
class clsFindUserScreen : public BaseScreen
{
public:
	static void ShowFindUser(UsersViewModel * usersViewModel) {
		_DrawScreenHeader("Find User Screen");
		unique_ptr<UserModel> UserToFind = make_unique<UserModel>();
		string Username = DataReader::ReadValidUsername();
		ResultStatus resultStatus = usersViewModel->searchUserByUsername(*UserToFind,Username);
		if (resultStatus == ResultStatus::Found)
		{
			cout << "\nThis user already exists and this is his information\n";
			UserToFind->PrintUser();
		}
		else {
			UserUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};