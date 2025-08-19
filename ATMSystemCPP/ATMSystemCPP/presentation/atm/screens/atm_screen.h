#pragma once
#include <vector>
#include <iostream>
#include "../../../core/utils/headers/console_helper.h"
#include "../../base/base_screen.h"
#include "normal_withdraw_screen.h"
#include "../../../view_model_provider/view_model_provider.h"
#include "../screens/quick_withdraw_screen.h"
#include "../../auth/screens/logout_screen.h"
#include "deposit_screen.h"
#include "check_balance_screen.h"
enum enMainMenuOptions
{
	eQuickWithdraw = 1, eNormalWithdraw, eDeposit, eCheckBalance, eLogout
};
class AtmScreen : public BaseScreen
{
	// Displays ATM main menu options
	static void ShowMainMenuOptions()
	{
		std::cout << "\t[1] Quick Withdraw.\n";
		std::cout << "\t[2] Normal Withdraw.\n";
		std::cout << "\t[3] Deposit.\n";
		std::cout << "\t[4] Check Balance.\n";
		std::cout << "\t[5] Logout.\n";
	}
	static void  ShowQuickWithdrawScreen() {
		QuickWithdrawScreen::ShowQuickWithdraw(ViewModelProvider::getATMViewMoel()); // Display the current account balance
	}
	static void  ShowNormalWithdrawScreen() {
		NormalWithdrawScreen::ShowNormalWithdrawScreen(ViewModelProvider::getATMViewMoel());
	}
	static void  ShowDepositScreen() {
		DepositScreen::showDeposit(ViewModelProvider::getATMViewMoel());
	}
	static void  ShowCheckBalanceScreen() {
		CheckBalanceScreen::showCheckBalance();
	}
	static void  ShowLogoutScreen() {
		LogoutScreen::showLogout(ViewModelProvider::getAuthViewModel());
	}
	// Executes the selected main menu option
	static void PerformMainMenuOption(const enMainMenuOptions& enMainMenuOption) {
		switch (enMainMenuOption) {
		case eQuickWithdraw:
			ConsoleHelper::ClearScreen(); // Clear the screen before showing quick withdraw options
			ShowQuickWithdrawScreen(); // Show the quick withdraw screen
			GoBackToMainMenu();
			break;
		case eNormalWithdraw:
			ConsoleHelper::ClearScreen(); // Clear the screen before showing normal withdraw options
			ShowNormalWithdrawScreen(); // Show the normal withdraw screen
			GoBackToMainMenu();
			break;
		case eDeposit:
			ConsoleHelper::ClearScreen(); // Clear the screen before showing deposit options
			ShowDepositScreen(); // Show the deposit screen
			GoBackToMainMenu();
			break;
		case eCheckBalance:
			ConsoleHelper::ClearScreen(); // Clear the screen before showing balance
			ShowCheckBalanceScreen(); // Show the current account balance
			GoBackToMainMenu();
			break;
		case eLogout:
			ConsoleHelper::ClearScreen();
			ShowLogoutScreen(); // Show the logout screen
			break;
		}
	}
	static void GoBackToMainMenu() {
		std::cout << "\n\n";
		std::cout << "\nPress any key to return to main menu...";
		system("pause>nul");
	}
public:
	static void ShowMainMenuScreen() {
		int choice;
		do
		{
			ConsoleHelper::ClearScreen(); // Clear the screen before showing the menu

			_DrawScreenHeader("ATM Main Menu Screen");

			ShowMainMenuOptions(); // Display main menu options

			std::cout << "=====================================\n";

			choice = DataReader::PromptAndReadIntNumber("Please enter your choice [1 - 5]: ");

			PerformMainMenuOption((enMainMenuOptions)choice); // Perform the action based on user choice

		} while (!CurrentSession::clientLogged->isEmpty()); // Exit on logout
	}
};

