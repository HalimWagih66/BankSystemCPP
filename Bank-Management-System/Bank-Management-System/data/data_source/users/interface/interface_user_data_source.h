#pragma once
#include <memory>
#include <string>
#include "../../../../core/types/result_status.h"
#include "../../../models/user_model.h"
#include <vector>

class IUsersDataSource
{
public:
    // Adds a new user to the data source
    virtual ResultStatus AddNewUser(const UserModel& User) = 0;

    // Updates an existing user in the data source
    virtual ResultStatus UpdateUser(const UserModel& User) = 0;

    // Deletes a user from the data source by username
    virtual ResultStatus DeleteUser(const std::string& Username) = 0;

    // Loads all users from the data source into the provided vector
    virtual ResultStatus GetAllUsers(std::vector<UserModel>& outUsers) = 0;

    // Finds a user by username and outputs the user object if found
    virtual ResultStatus FindUserByUsername(UserModel& User, const std::string& Username) = 0;
};