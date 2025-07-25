#include "../../users/helpers/user_ui_helpers.h"
#include "../../../core/utils/headers/data_reader.h"
#include "../view_model/auth_view_model.h"
#include "../../base/base_screen.h"
#include <iostream>
class  LogoutScreen : protected BaseScreen
{
public:
	static void showLogout(AuthViewModel* authViewModel) {
		_DrawScreenHeader("\tLogout Screen");
		std::cout << "\n\n";
		if (DataReader::Confirm("Do you really want to logout Y/N? "))
		{
			ResultStatus resultStatusLogout = authViewModel->logout();
			if (resultStatusLogout == ResultStatus::Success)
			{
				std::cout << "\n\nYou have been logged out successfully.\n\n";
			}
			else
			{
				UserUIHelpers::DisplayResultMessage(resultStatusLogout);
			}
		}
		else
		{
			std::cout << "Logout cancelled.\n\n";
			return;
		}
	}
};