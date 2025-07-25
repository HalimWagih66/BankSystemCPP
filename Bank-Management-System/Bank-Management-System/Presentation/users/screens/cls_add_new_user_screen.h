#pragma once
#include "../../base/base_screen.h"
#include "../helpers/user_ui_helpers.h"
#include "../../../core/utils/headers/data_reader.h"
#include "../../../core/constants/Permissions/permissions_constants.h"
class clsAddNewUserScreen : public BaseScreen
{
private:
	static void _goToMainScreen() {
		cout << "You have successfully logged in. Press any key to enter the manage users menu...\n";
		system("pause>0");
	}
	static UserModel _readUserInfo() {
		string firstName = DataReader::ReadValidName("First");
		string lastName = DataReader::ReadValidName("Last");
		string Username = DataReader::ReadValidUsername();
		string PhoneNumber = DataReader::ReadValidPhoneNumber();
		string Email = DataReader::ReadValidEmail();
		string Password = DataReader::ReadValidPassword();
		short Permissions = DataReader::ReadPermissions(PermissionsConstants::getPermissionsList());
		return UserModel(firstName,lastName,Email,PhoneNumber, Username,Password,Permissions);
	}
public:
	static void ShowAddNewUser(UsersViewModel* usersViewModel) {
		_DrawScreenHeader("\t  Add New User Screen");
		UserModel NewUser = _readUserInfo();
		ResultStatus resultStatusAddUser;
		do
		{
			ResultStatus resultStatusAddUser = usersViewModel->AddNewUser(NewUser);
			if (resultStatusAddUser == ResultStatus::Success)
			{
				cout << "The new user has been added successfully with this information.\n";
				NewUser.PrintUser();
				return;
			}
			else if(resultStatusAddUser == ResultStatus::Found){
				cout << "The username you entered already exists. Enter a new username"<<endl;
				NewUser.Username = DataReader::ReadValidUsername();
			}
			else
			{
				UserUIHelpers::DisplayResultMessage(resultStatusAddUser);
				cout << "\n";
				return;
			}
		} while (true);
	}
};

