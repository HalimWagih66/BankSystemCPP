#pragma once
#include <iostream>
#include <string>
#include "../../core/utils/headers/date_utils.h"
#include "../../core/session/current_session.h"
class BaseScreen
{
protected:
    static void _DrawScreenHeader(std::string screenName) {
        std::cout << "\n==================================================\n\n";
        std::cout << "\t" << screenName << std::endl;
        std::cout << "\n==================================================\n\n";
    }
};