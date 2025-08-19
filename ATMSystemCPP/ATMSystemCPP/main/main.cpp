#include <iostream>
#include "../presentation/auth/screens/login_screen.h"
#include "../view_model_provider/view_model_provider.h"
#include "../presentation/atm/screens/atm_screen.h"
#include "../core/types/result_status.h"
using namespace std;
int main() {
	ResultStatus resultStatus;
	do
	{
		resultStatus = LoginScreen::ShowLogin(ViewModelProvider::getAuthViewModel());
		if (resultStatus == ResultStatus::Success)
		{
			AtmScreen::ShowMainMenuScreen();
		}
	} while (true);
	return 0;
}