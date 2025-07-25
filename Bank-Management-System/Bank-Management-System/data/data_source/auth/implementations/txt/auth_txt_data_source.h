#pragma once
#include <string>
#include <vector>
#include "../../../../../core/types/result_status.h"
#include <memory>
#include "../../../../models/login_register_model.h"
#include "../../interface/interface_auth_data_source.h"
#include "../../../../models/user_model.h"

class AuthTxtDataSource : public IAuthDataSource
{
    // Converts a log line to a LoginRegisterModel object
    LoginRegisterModel _ConvertLineToRegisterRecord(std::string line, std::string seperator = "#//#");

    // Converts a user line to a UserModel object
    UserModel _ConvertLineToUserObject(std::string Line, std::string Seperator = "#//#");

    // Loads all users from the file into the provided vector
    ResultStatus _GetAllUsers(std::vector<UserModel>& vUsers);

    // Prepares a login record string for saving to file
    std::string _PrepareLoginRecord(LoginRegisterModel LoginRegisterRecord, std::string seperator = "#//#");

    // Private constructor for singleton pattern
    AuthTxtDataSource();

    // Singleton instance pointer
    static std::unique_ptr<AuthTxtDataSource> _Instance;
public:
    // Logs out the current user
    ResultStatus Logout();

    // Attempts to log in a user and outputs the user object if found
    ResultStatus LoginUser(const std::string& Username, const std::string& Password, UserModel& outUser);

    // Loads all login/register logs from the file
    ResultStatus GetRegisterLoginLogs(std::vector<LoginRegisterModel>& vLoginRegisterRecords);

    // Saves a login/register log record to the file
    ResultStatus RegisterLoginLog(const LoginRegisterModel& loginRegisterRecord);

    // Returns the singleton instance of AuthTxtDataSource
    static AuthTxtDataSource* getInstance();
};