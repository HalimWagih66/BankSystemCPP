#pragma once

#include "../../../data/data_source/users/interface/interface_user_data_source.h"
#include <memory>
#include <string>
#include "../../../core/types/result_status.h"
#include "../../../data/models/user_model.h"
#include <vector>

// ViewModel responsible for managing user accounts (add, update, remove, search, etc.)
class UsersViewModel
{
private:
    // Pointer to the data source interface for user operations
    IUsersDataSource* _userDataSource;

    // Singleton instance of the UsersViewModel
    static std::unique_ptr<UsersViewModel> _instance;

    // Private constructor to enforce singleton pattern
    UsersViewModel(IUsersDataSource* usersDataUsers);

    // Helper method to check if a username already exists
    bool _isUsernameExist(const std::string& Username);

public:
    // Returns the singleton instance, creating it if it doesn't exist
    static UsersViewModel* getInstance(IUsersDataSource* usersDataUsers);

    // Removes a user by username
    ResultStatus removeUser(const std::string& Username);

    // Adds a new user, returns Found if the username already exists
    ResultStatus AddNewUser(const UserModel& userModel);

    // Updates existing user's data
    ResultStatus updateUser(const UserModel& userModel);

    // Searches for a user by username and stores the result in outUser
    ResultStatus searchUserByUsername(UserModel& outUser, const std::string& Username);

    // Retrieves a list of all users and stores them in the provided vector
    ResultStatus getUsers(std::vector<UserModel>& userModel);
};
