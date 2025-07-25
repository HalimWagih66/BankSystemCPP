#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../../../../core/types/result_status.h"
#include "../../../models/user_model.h"
#include "../../../models/login_register_model.h"

class IAuthDataSource
{
public:
    // Attempts to log in a user with the given username and password.
    // If successful, fills outUser with user data and returns ResultStatus::Found.
    virtual ResultStatus LoginUser(const std::string& Username, const std::string& Password, UserModel& outUser) = 0;

    // Logs out the current user/session.
    virtual ResultStatus Logout() = 0;

    // Loads all login/register activity logs into the provided vector.
    virtual ResultStatus GetRegisterLoginLogs(std::vector<LoginRegisterModel>& vTrnsferLogRecord) = 0;

    // Saves a login/register activity record to the log.
    virtual ResultStatus RegisterLoginLog(const LoginRegisterModel& loginRegisterRecord) = 0;
};