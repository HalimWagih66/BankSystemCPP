#pragma once

// Include screens and utilities
#include "clients/screens/cls_add_new_client_screen.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include "base/base_screen.h"
#include "../core/utils/headers/console_helper.h"
#include "../di/view_model_provider/view_model_provider.h"
#include "clients/screens/cls_client_list_screen.h"
#include "currencies/screens/currency_exchange_main_screen.h"
#include "clients/screens/cls_delete_client_screen.h"
#include "clients/screens/cls_update_client_screen.h"
#include "clients/screens/cls_find_client_screen.h"
#include "users/screens/cls_manage_users_screen.h"
#include "auth/screens/logout_screen.h"
#include "transactions/screens/cls_transactions_screen.h"
#include "../Presentation/auth/screens/login_register_Screen.h"

// Main menu screen class, inherits from BaseScreen
class clsMainScreen : protected BaseScreen
{
private:
    // Enum representing each main menu option
    enum enMainMenueOptions {
        eShowClientList = 1,
        eAddNewClient,
        eDeleteClient,
        eUpdateClientInfo,
        eFindClient,
        eTransactions,
        eManageUsers,
        eLoginRegister,
        eCurrencyExchange,
        eLogout = 10
    };

    // Reads and validates the user's menu selection
    static short _ReadMainMenueOption() {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 9]? ";
        short Choice = DataReader::ReadShortNumberBetween(1, 9, "Enter Number between 1 to 9? ");
        return Choice;
    }

    // Individual menu option handlers
    static void _ShowAllClientsScreen() {
        clsClientListScreen::ShowClientsList(ViewModelProvider::getClientsViewModel());
    }

    static void _ShowAddNewClientsScreen() {
        clsAddNewClientScreen::ShowAddNewClientScreen(ViewModelProvider::getClientsViewModel());
    }

    static void _ShowDeleteClientScreen() {
        clsDeleteClientScreen::ShowDeleteClientScreen(ViewModelProvider::getClientsViewModel());
    }

    static void _ShowUpdateClientInfoScreen() {
        clsUpdateClientScreen::ShowUpdateClient(ViewModelProvider::getClientsViewModel());
    }

    static void _ShowFindClientScreen() {
        clsFindClientScreen::ShowFindClientScreen(ViewModelProvider::getClientsViewModel());
    }

    static void _ShowTransactionsScreen() {
        std::unique_ptr<clsTransactionsScreen> manageUsersScreen = std::make_unique<clsTransactionsScreen>(ViewModelProvider::getTransactionsViewModel());
        manageUsersScreen->ShowTransactionsMenue();
    }

    static void _ShowManageUsersScreen() {
        std::unique_ptr<clsManageUsersScreen> manageUsersScreen = std::make_unique<clsManageUsersScreen>(ViewModelProvider::getUsersViewModel());
        manageUsersScreen->ShowManageUsersMenue();
    }

    static void _ShowCurrenciesScreen() {
        std::unique_ptr<clsCurrencyExchangeMainScreen> currencyExchangeMainScreen = std::make_unique<clsCurrencyExchangeMainScreen>(ViewModelProvider::getCurrenciesViewModel());
        currencyExchangeMainScreen->ShowCurrenciesMenue();
    }

    static void _ShowLogoutScreen() {
        LogoutScreen::showLogout(ViewModelProvider::getAuthViewModel());
        // Return to main menu if logout was cancelled
        if (!CurrentSession::UserLogged->isEmpty()) {
            _GoBackToMainScreen();
        }
    }

    // Waits for user to press a key, then returns to the main screen
    static void _GoBackToMainScreen() {
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowLoginRegisterScreen() {
        LoginRegisterScreen::ShowLoginRegister(ViewModelProvider::getAuthViewModel());
    }

    // Executes the action corresponding to the selected menu option
    static void _PerfromMainMenueOption(enMainMenueOptions Option) {
        switch (Option) {
        case enMainMenueOptions::eShowClientList:
            ConsoleHelper::ClearScreen();
            _ShowAllClientsScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eAddNewClient:
            ConsoleHelper::ClearScreen();
            _ShowAddNewClientsScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eDeleteClient:
            ConsoleHelper::ClearScreen();
            _ShowDeleteClientScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eUpdateClientInfo:
            ConsoleHelper::ClearScreen();
            _ShowUpdateClientInfoScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eFindClient:
            ConsoleHelper::ClearScreen();
            _ShowFindClientScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eTransactions:
            ConsoleHelper::ClearScreen();
            _ShowTransactionsScreen();
            ShowMainMenue();
            break;
        case enMainMenueOptions::eManageUsers:
            ConsoleHelper::ClearScreen();
            _ShowManageUsersScreen();
            ShowMainMenue();
            break;
        case enMainMenueOptions::eLoginRegister:
            ConsoleHelper::ClearScreen();
            _ShowLoginRegisterScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eCurrencyExchange:
            ConsoleHelper::ClearScreen();
            _ShowCurrenciesScreen();
            _GoBackToMainScreen();
            break;
        case enMainMenueOptions::eLogout:
            ConsoleHelper::ClearScreen();
            _ShowLogoutScreen();
            break;
        }
    }

public:
    // Displays the main menu and handles user input in a loop
    static void ShowMainMenue()
    {
        enMainMenueOptions MainMenueOption;
        do
        {
            ConsoleHelper::ClearScreen();
            _DrawScreenHeader("\t\tMain Screen");

            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t\t\tMain Menue\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t[1] Show Client List.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[2] Add New Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[4] Update Client Info.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[6] Transactions.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[7] Manage Users.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[8] Login Register.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[9] Currency Exchange\n";
            std::cout << std::setw(37) << std::left << "" << "\t[10] Logout.\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";

            // Read user input and perform the selected action
            MainMenueOption = (enMainMenueOptions)_ReadMainMenueOption();
            _PerfromMainMenueOption(MainMenueOption);

        } while (MainMenueOption != enMainMenueOptions::eLogout);
    }
};
