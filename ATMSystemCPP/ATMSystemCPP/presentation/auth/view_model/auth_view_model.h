#pragma once
#include <string>
#include <memory>
#include <vector>
#include "auth_view_model.h"
#include "../../../data/data_source/auth/interface/interface_auth_data_source.h"
class AuthViewModel
{
    // Pointer to the authentication data source (handles login, logout, and log history)
    IAuthDataSource* _authDataSource;

    // Singleton instance of AuthViewModel
    static std::unique_ptr<AuthViewModel> _instance;

    // Private constructor to prevent direct instantiation
    AuthViewModel(IAuthDataSource* authDataSource);

public:
    // Authenticates the user using username and password
    // If successful, stores the user in the current session and registers the login
    ResultStatus login(const std::string& username, const std::string& password);

    // Logs out the current user
    ResultStatus logout();

    // Gets the singleton instance of AuthViewModel (creates one if it doesn't exist)
    static AuthViewModel* getInstance(IAuthDataSource* authDataSource);
};
