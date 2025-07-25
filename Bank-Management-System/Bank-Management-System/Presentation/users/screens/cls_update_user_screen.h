#pragma once
#include "../helpers/user_ui_helpers.h"
#include <memory>
#include "../../../core/types/result_status.h"
#include <string>
#include <memory>
#include "../../../data/models/user_model.h"
class clsUpdateUserScreen : public BaseScreen
{
	static ResultStatus _GetUserToUpdate(UsersViewModel* usersViewModel, UserModel& outUser) {
		std::string Username;
		ResultStatus resultStatus;
		do
		{
			Username = DataReader::ReadValidUsername();
			resultStatus = usersViewModel->searchUserByUsername(outUser, Username);
			if (resultStatus == ResultStatus::Found)
			{
				return ResultStatus::Found;
			}
			else if (resultStatus == ResultStatus::NotFound) {
				UserUIHelpers::DisplayResultMessage(resultStatus);
				if (!DataReader::Confirm("Do you want to reuse the username? (Y/N)? "))
				{
					return ResultStatus::CancelledOperation;
				}
			}
			else if (resultStatus == ResultStatus::Failed)
			{
				return ResultStatus::Failed;
			}
		} while (resultStatus == ResultStatus::NotFound);
	}
	static void ReadNewUserInfo(UserModel& User) {

		if (DataReader::AreYouSure("Are You Want Edit First Name? (Y/N): "))
			User.FirstName =DataReader::ReadValidName("First");

		if (DataReader::AreYouSure("Are You Want Edit Last Name? (Y/N): "))
			User.LastName =DataReader::ReadValidName("Last");

		if (DataReader::AreYouSure("Are You Want Edit Email? (Y/N): "))
			User.Email =DataReader::ReadValidEmail();

		if (DataReader::AreYouSure("Are You Want Edit Phone Number? (Y/N): "))
			User.PhoneNumber =DataReader::ReadValidPhoneNumber();

		if (DataReader::AreYouSure("Are You Want Edit Password? (Y/N): "))
			User.Password =DataReader::ReadValidPassword();

		if (DataReader::AreYouSure("Are You Want Edit Permissions? (Y/N): "))
			User.Permissions =DataReader::ReadPermissions(PermissionsConstants::getPermissionsList());

		cout << "\n______________________________\n";
	}
public:
	static void ShowUpdateUserScreen(UsersViewModel* usersViewModel) {
		_DrawScreenHeader("\tUpdate User Screen");
		unique_ptr<UserModel> UserToUpdate = make_unique<UserModel>();
		ResultStatus resultStatus = _GetUserToUpdate(usersViewModel,*UserToUpdate);
		if (resultStatus == ResultStatus::Found)
		{
			cout << "\n\tThis is user information.\n";
			UserToUpdate->PrintUser();
			if (DataReader::Confirm("Are you want update this user? (Y/N)? "))
			{
				cout << "\n\tPlease enter the new information.\n";
				ReadNewUserInfo(*UserToUpdate);
				ResultStatus resultStatusUpdateUser = usersViewModel->updateUser(*UserToUpdate);
				if (resultStatusUpdateUser == ResultStatus::Success)
				{
					cout << "\nUser updated successfully.\n";
					cout << "\n User info after update:\n";
					UserToUpdate->PrintUser();
				}
				else
				{
					UserUIHelpers::DisplayResultMessage(resultStatusUpdateUser);
				}
			}
			else
			{
				cout << "\n\tUpdate user operation cancelled.\n";
			}
		}
		else {
			UserUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};

