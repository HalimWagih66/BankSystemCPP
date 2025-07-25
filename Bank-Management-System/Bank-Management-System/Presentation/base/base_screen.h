#pragma once
#include <iostream>
#include <string>
#include "../../core/utils/headers/date_utils.h"
#include "../../core/session/current_session.h"
class BaseScreen
{
protected:
    static void _DrawScreenHeader(std::string Title, std::string SubTitle = "") {
        std::cout << "\t\t\t\t\t______________________________________";
        std::cout << "\n\n\t\t\t\t\t  " << Title << "\n";
        if (SubTitle != "")
        {
            std::cout << "\n\t\t\t\t\t  " << SubTitle << "\n";
        }
        std::cout << "\t\t\t\t\t______________________________________\n\n";
        std::cout << "\t\t\t\t\t  Username : " << CurrentSession::UserLogged->Username << "\n\n";
        std::cout << "\t\t\t\t\t  Date : " << DateUtils::DateToString(DateUtils()) << "\n\n";
    }
    static bool CheckAccessRights(UserModel::enPermissions Permission)
    {
        if (!CurrentSession::UserLogged->CheckAccessPermission(Permission))
        {
			Messages::ShowAccessDeniedMessage();
            return false;
        }
        else
        {
            return true;
        }
    }
};