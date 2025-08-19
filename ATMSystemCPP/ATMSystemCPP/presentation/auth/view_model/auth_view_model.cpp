#include "auth_view_model.h"
#include "../../../data/data_source/auth/interface/interface_auth_data_source.h"
#include <memory>
#include <string>
#include <vector>
#include "../../../core/session/current_session.h"
#include "../../../core/utils/headers/date_utils.h"
#include "../../../data/models/bank_client_model.h"
using namespace std;

// Define the static singleton instance of AuthViewModel
unique_ptr<AuthViewModel> AuthViewModel::_instance = nullptr;

// Constructor - takes an authentication data source to interact with
AuthViewModel::AuthViewModel(IAuthDataSource* authDataSource)
{
    _authDataSource = authDataSource;
}

ResultStatus AuthViewModel::login(const std::string& accountNumber, const std::string& pinCode)
{
    return _authDataSource->Login(accountNumber, pinCode, *CurrentSession::clientLogged);
}

// Performs logout by calling the data source's logout logic
ResultStatus AuthViewModel::logout()
{
    return _authDataSource->Logout();
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
