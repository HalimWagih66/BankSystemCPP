#pragma once
#include <iostream>
#include <iomanip>
#include "../../data/data_source/users/interface/interface_user_data_source.h"
#include "../../core/utils/headers/data_reader.h"
#include "cls_add_new_user_screen.h"
#include "user_list_screen.h"
#include "cls_update_user_screen.h"
#include "../../Users/screens/cls_find_user_screen.h"
#include "../../Users/screens/cls_delete_user_screen.h"
#include "../../base/base_screen.h"
#include "../../../core/utils/headers/console_helper.h"
#include "../view_model/users_view_model.h"
using namespace std;
class clsManageUsersScreen : protected BaseScreen
{
    UsersViewModel* usersViewModel;
    enum enManageUsersMenueOptions
    {
        eListUsers = 1,
        eAddNewUser,
        eDeleteUser,
        eUpdateUser,
        eFindUser,
        eMainMenue
    };
    short _ReadTransactionsMenueOption() {
        cout << std::setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = DataReader::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }
    void _ShowListUsersScreen() {
        UserListScreen::ShowUserList(usersViewModel);
    }
    void _ShowAddNewUserScreen() {
        clsAddNewUserScreen::ShowAddNewUser(usersViewModel);
    }
    void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUser(usersViewModel);
    }
    void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen(usersViewModel);
    }
    void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUser(usersViewModel);
    }
    void _ShowMainMenue() {

    }
    void _PerformManageUsersMenueOption(enManageUsersMenueOptions Option)
    {

        switch (Option)
        {
        case eListUsers:
            ConsoleHelper::ClearScreen();
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case eAddNewUser:
            ConsoleHelper::ClearScreen();
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case eDeleteUser:
            ConsoleHelper::ClearScreen();
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case eUpdateUser:
            ConsoleHelper::ClearScreen();
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case eFindUser:
            ConsoleHelper::ClearScreen();
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case eMainMenue:
            ConsoleHelper::ClearScreen();
            _ShowMainMenue();
            break;
        default:
            cout << "Invalid Option!" << endl;
            break;
        }
    }
    void _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowManageUsersMenue();
    }
public:
    clsManageUsersScreen(UsersViewModel* usersViewModel) {
        this->usersViewModel = usersViewModel;
    }
    void ShowManageUsersMenue()
    {
        if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pManageUsers)) return;

        ConsoleHelper::ClearScreen();
        _DrawScreenHeader("\t Manage Users Screen");

        cout << std::setw(37) << left << "" << "===========================================\n";
        cout << std::setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << std::setw(37) << left << "" << "===========================================\n";
        cout << std::setw(37) << left << "" << "\t[1] List Users.\n";
        cout << std::setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << std::setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << std::setw(37) << left << "" << "\t[4] Update User.\n";
        cout << std::setw(37) << left << "" << "\t[5] Find User.\n";
        cout << std::setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << std::setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadTransactionsMenueOption());
    }
};
