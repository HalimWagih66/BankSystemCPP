#pragma once
#include "../../../data/data_source/users/interface/interface_user_data_source.h"
#include "../../base/base_screen.h"
#include "../../../data/models/user_model.h"
#include <string>
#include "../helpers/user_ui_helpers.h"
class clsDeleteUserScreen : public BaseScreen
{
	static void removeUserProcess(const UserModel& userToDelete, UsersViewModel* usersViewModel) {
		cout << "\nThis user already exists\n";
		userToDelete.PrintUser();
		if (userToDelete.Username == "Halim_Wagih")
		{
			cout << "It is forbidden to delete the admin" << endl;
			return;
		}
		if (DataReader::AreYouSure("Are you sure you want to delete this User (Y/N)? "))
		{
			ResultStatus resultStatusDeleteUser = usersViewModel->removeUser(userToDelete.Username);
			if (resultStatusDeleteUser == ResultStatus::Success)
			{
				UserUIHelpers::DisplayResultMessage(resultStatusDeleteUser, "This user has already been deleted.");
			}
			else
			{
				UserUIHelpers::DisplayResultMessage(resultStatusDeleteUser);
			}
		}
		else
		{
			std::cout << "\nThis operation has been canceled.\n";
		}
	}
public:
	static void ShowDeleteUser(UsersViewModel* usersViewModel){
		_DrawScreenHeader("\tDelete User Screen");
		unique_ptr<UserModel> userToDelete = make_unique<UserModel>();
		string Username = DataReader::ReadValidUsername();
		ResultStatus resultStatus = usersViewModel->searchUserByUsername(*userToDelete,Username);
		if (resultStatus == ResultStatus::Found)
		{
			removeUserProcess(*userToDelete, usersViewModel);
		}
		else {
			UserUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};