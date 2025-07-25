#pragma once
#include "../../data/models/user_model.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "../../base/base_screen.h"
#include "../helpers/user_ui_helpers.h"
class UserListScreen : public BaseScreen
{
private:
    static void _PrintUserRecordLine(const UserModel& User)
    {
        
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(12) << std::left << User.Username;
        std::cout << "| " << std::setw(25) << std::left << User.GetFullName();
        std::cout << "| " << std::setw(12) << std::left << User.PhoneNumber;
        std::cout << "| " << std::setw(28) << std::left << User.Email;
        std::cout << "| " << std::setw(18) << std::left << User.Password;
        std::cout << "| " << std::setw(12) << std::left << User.Permissions;
        
    }
    static void _DisplayUserListTable(std::vector<UserModel>&vUsers) {
        _displayUserListTableHeader();
        _DisplayUserListTableBody(vUsers);
    }
    static void Seperator() {
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_________________________________________________________________\n" << endl;
    }
    static void _displayUserListTableHeader() {
        Seperator();

        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(12) << "UserName";
        std::cout << "| " << std::left << std::setw(25) << "Full Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(28) << "Email";
        std::cout << "| " << std::left << std::setw(18) << "Password";
        std::cout << "| " << std::left << std::setw(12) << "Permissions";
        Seperator();
    }
    static void _DisplayUserListTableBody(std::vector<UserModel>& vUsers) {
        if (vUsers.size() == 0)
            std::cout << "\t\t\t\t\tNo Users Available In the System!";
        else

            for (const UserModel& User : vUsers)
            {

                _PrintUserRecordLine(User);
                std::cout << endl;
            }

        Seperator();
    }
public:
    static void ShowUserList(UsersViewModel * usersViewModel) {
        std::unique_ptr<std::vector<UserModel>> vUsers = std::make_unique<std::vector<UserModel>>();
        ResultStatus resultStatus = usersViewModel->getUsers(*vUsers);
        if (resultStatus != ResultStatus::Success)
        {
            _DrawScreenHeader("\t  User List Screen");
            UserUIHelpers::DisplayResultMessage(resultStatus);
            return;
        }
        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers->size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);
        _DisplayUserListTable(*vUsers);
    }
};
