#pragma once
#include <array>
#include <string>

class PermissionsConstants {
public:
    static std::array<std::string, 9> getPermissionsList() {
        return {
            "Show Client List? Y/N? ",
            "Add New Client? Y/N? ",
            "Delete Client? Y/N? ",
            "Update Client? Y/N? ",
            "Find Client? Y/N? ",
            "Transaction? Y/N? ",
            "Manage Users? Y/N? ",
            "Login Register? Y/N ",
            "Currency Exchange? Y/N ",
        };
    }
};
