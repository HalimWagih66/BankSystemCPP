#pragma once
#include <string>
#include "../../../../core/types/result_status.h"
#include "../../../models/bank_client_model.h"
class IAuthDataSource
{
public:
    // Attempts to log in a client by Account number and Pin code
    virtual ResultStatus Login(const std::string& accountNumber, const std::string& pinCode,BankClientModel& bankClientModel) = 0;

    // Logs out the current user by resetting the session
    virtual ResultStatus Logout() = 0;
 
};