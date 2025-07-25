#include "users_view_model.h"
#include <vector>
#include "../../../core/types/result_status.h"
#include <memory>
#include "../../../data/models/user_model.h"
#include "../../../data/models/login_register_model.h"

using namespace std;

// Initialize the singleton instance pointer to null
unique_ptr<UsersViewModel> UsersViewModel::_instance = nullptr;

// Private constructor: accepts a user data source dependency
UsersViewModel::UsersViewModel(IUsersDataSource* userDataSource) {
    _userDataSource = userDataSource;
}

// Checks if a username already exists in the system
bool UsersViewModel::_isUsernameExist(const string& Username)
{
    unique_ptr<UserModel> user = make_unique<UserModel>();
    ResultStatus resultStatusSearch = searchUserByUsername(*user, Username);

    if (resultStatusSearch == ResultStatus::Found) {
        return true;
    }
    else {
        return false;
    }
}

// Retrieves all users from the data source
ResultStatus UsersViewModel::getUsers(vector<UserModel>& outUsers) {
    unique_ptr<vector<UserModel>> vUsers = make_unique<vector<UserModel>>();
    ResultStatus resultStatus = _userDataSource->GetAllUsers(*vUsers);

    if (resultStatus == ResultStatus::Success) {
        outUsers = move(*vUsers);
    }
    return resultStatus;
}

// Updates a user's information
ResultStatus UsersViewModel::updateUser(const UserModel& userModel) {
    return _userDataSource->UpdateUser(userModel);
}

// Removes a user by their username
ResultStatus UsersViewModel::removeUser(const string& Username) {
    return _userDataSource->DeleteUser(Username);
}

// Searches for a user by username, and stores result in outUser
ResultStatus UsersViewModel::searchUserByUsername(UserModel& outUser, const string& Username)
{
    // Allocate an empty UserModel pointer
    unique_ptr<UserModel> UserPtr = unique_ptr<UserModel>();

    // Attempt to find user in data source
    ResultStatus resultStatusFind = _userDataSource->FindUserByUsername(*UserPtr, Username);

    if (resultStatusFind == ResultStatus::Found) {
        outUser = move(*UserPtr); // move contents to output
    }
    return resultStatusFind;
}

// Adds a new user if the username does not already exist
ResultStatus UsersViewModel::AddNewUser(const UserModel& userModel) {
    if (_isUsernameExist(userModel.Username)) {
        return ResultStatus::Found; // Prevent duplicate usernames
    }
    return _userDataSource->AddNewUser(userModel);
}

// Singleton accessor - creates the instance if it doesn't exist yet
UsersViewModel* UsersViewModel::getInstance(IUsersDataSource* usersDataSource)
{
    if (_instance == nullptr) {
        _instance = unique_ptr<UsersViewModel>(new UsersViewModel(usersDataSource));
    }
    return _instance.get();
}
