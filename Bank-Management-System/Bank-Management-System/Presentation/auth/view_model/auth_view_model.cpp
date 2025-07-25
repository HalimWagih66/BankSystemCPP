#include "auth_view_model.h"
#include "../../../data/data_source/auth/interface/interface_auth_data_source.h"
#include <memory>
#include <string>
#include <vector>
#include "../../../data/models/login_register_model.h"
#include "../../../core/session/current_session.h"
#include "../../../core/utils/headers/date_utils.h"
using namespace std;

// Define the static singleton instance of AuthViewModel
unique_ptr<AuthViewModel> AuthViewModel::_instance = nullptr;

// Constructor - takes an authentication data source to interact with
AuthViewModel::AuthViewModel(IAuthDataSource* authDataSource)
{
    _authDataSource = authDataSource;
}

// Handles login logic using username and password
// If the user is found, store them in the current session and register the login event
ResultStatus AuthViewModel::login(const std::string& username, const std::string& password)
{
    UserModel foundUser;
    ResultStatus resultStatus = _authDataSource->LoginUser(username, password, foundUser);

    if (resultStatus == ResultStatus::Found)
    {
        // Store the logged-in user in the global session
        *CurrentSession::UserLogged = foundUser;

        // Register this login attempt in the login history
        return registerUser();
    }

    return resultStatus;
}

// Registers a login entry in the login history/log file
ResultStatus AuthViewModel::registerUser()
{
    unique_ptr<LoginRegisterModel> loginRegisterModel = make_unique<LoginRegisterModel>();

    // Fill the login log model with current user's data
    loginRegisterModel->Username = CurrentSession::UserLogged->Username;
    loginRegisterModel->Password = CurrentSession::UserLogged->Password;
    loginRegisterModel->Permissions = CurrentSession::UserLogged->Permissions;
    loginRegisterModel->SetDateTime(DateUtils::GetSystemDateTimeString());

    // Pass the model to the data source for saving
    return _authDataSource->RegisterLoginLog(*loginRegisterModel);
}

// Performs logout by calling the data source's logout logic
ResultStatus AuthViewModel::logout()
{
    return _authDataSource->Logout();
}

// Retrieves all previous login records and stores them in the provided vector
ResultStatus AuthViewModel::getRegisterLoginLogs(vector<LoginRegisterModel>& vLoginRegisterRecords)
{
    unique_ptr<vector<LoginRegisterModel>> loginRecords = make_unique<vector<LoginRegisterModel>>();

    ResultStatus resultStatus = _authDataSource->GetRegisterLoginLogs(*loginRecords);

    if (resultStatus == ResultStatus::Success)
    {
        // Move the records to the caller's vector
        vLoginRegisterRecords = std::move(*loginRecords);
    }

    return resultStatus;
}

// Singleton access method - creates the instance only once and returns a raw pointer
AuthViewModel* AuthViewModel::getInstance(IAuthDataSource* authDataSource)
{
    if (_instance == nullptr)
    {
        _instance = unique_ptr<AuthViewModel>(new AuthViewModel(authDataSource));
    }
    return _instance.get();
}
