#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../../../../models/user_model.h"
#include "../../interface/interface_user_data_source.h"

class UserTxtDataSource : public IUsersDataSource
{
private:
    // Converts a line from the file into a UserModel object
    UserModel _ConvertLineToUserObject(std::string Line, std::string Seperator = "#//#");

    // Converts a UserModel object to a string line for file storage
    std::string _ConverUserObjectToLine(UserModel User, std::string Seperator = "#//#");

    // Compares two usernames for equality (case-insensitive, trimmed)
    bool _IsSameUsername(const std::string& Username, const std::string& Username2);

    // Saves all users to the file, skipping those marked for deletion
    ResultStatus _SaveUsers(const std::vector<UserModel>& vUsers);

    // Private constructor for singleton pattern
    UserTxtDataSource();

    // Singleton instance pointer
    static std::unique_ptr<UserTxtDataSource> _instance;
public:
    // Updates an existing user in the file
    ResultStatus UpdateUser(const UserModel& outUser);

    // Adds a new user to the file
    ResultStatus AddNewUser(const UserModel& User);

    // Deletes a user by marking for deletion and saving the updated list
    ResultStatus DeleteUser(const std::string& Username);

    // Finds a user by username and outputs the user object if found
    ResultStatus FindUserByUsername(UserModel& UserF, const std::string& Username);

    // Loads all users from the file into the provided vector
    ResultStatus GetAllUsers(std::vector<UserModel>& vUsers);

    // Returns the singleton instance of UserTxtDataSource
    static UserTxtDataSource* getInstance();
};