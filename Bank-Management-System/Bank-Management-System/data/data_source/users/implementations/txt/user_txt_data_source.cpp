#include "user_txt_data_source.h"
#include <memory>
#include "../../../../../core/utils/headers/string_utils.h"
#include "../../../../../core/utils/headers/encryption.h"
#include <vector>
#include "../../../../models/user_model.h"
#include "../../../../../core/constants/file_pathes/file_pathes.h"
#include "../../../../services/txt/file_txt_manager.h"
using namespace std;

// Singleton instance initialization
unique_ptr<UserTxtDataSource> UserTxtDataSource::_instance = nullptr;

// Constructor
UserTxtDataSource::UserTxtDataSource() {}

// Converts a line from file into a UserModel object
UserModel UserTxtDataSource::_ConvertLineToUserObject(string Line, string Seperator)
{
	vector<string> vUserData = StringUtils::SplitString(Line, Seperator);

	return UserModel(vUserData[0], vUserData[1], vUserData[2],
		vUserData[3], vUserData[4], Encryption::DecryptText(vUserData[5]), stoi(vUserData[6]));
}

// Converts a UserModel object into a line for file saving
string UserTxtDataSource::_ConverUserObjectToLine(UserModel User, string Seperator)
{
	string userRecord = "";
	userRecord += User.FirstName + Seperator;
	userRecord += User.LastName + Seperator;
	userRecord += User.Email + Seperator;
	userRecord += User.PhoneNumber + Seperator;
	userRecord += User.Username + Seperator;
	userRecord += Encryption::EncryptText(User.Password) + Seperator;
	userRecord += to_string(User.Permissions);

	return userRecord;
}

// Compares two usernames after trimming and converting to uppercase
bool UserTxtDataSource::_IsSameUsername(const string& Username, const string& Username2) {
	return (StringUtils::ToUpperCase(StringUtils::TrimString(Username)) ==
		StringUtils::ToUpperCase(StringUtils::TrimString(Username2)));
}

// Saves the list of users to the text file (ignores deleted users)
ResultStatus UserTxtDataSource::_SaveUsers(const vector<UserModel>& vUsers) {
	vector<string> vClientsString;
	for (const UserModel& User : vUsers)
	{
		if (!User.MarkedForDelete)
		{
			vClientsString.push_back(_ConverUserObjectToLine(User));
		}
	}
	try {
		FileTxtManager::SaveLinesInFile(vClientsString, FilePathes::USERS);
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Updates an existing user in the file
ResultStatus UserTxtDataSource::UpdateUser(const UserModel& outUser) {
	unique_ptr<vector<UserModel>> vUsers = make_unique<vector<UserModel>>();
	ResultStatus resultStatus = GetAllUsers(*vUsers);
	if (resultStatus == ResultStatus::Success)
	{
		for (UserModel& User : *vUsers)
		{
			if (_IsSameUsername(User.Username, outUser.Username)) {
				User = outUser;
				User.FirstName = outUser.FirstName; // Extra step, maybe redundant
				return _SaveUsers(*vUsers);
			}
		}
		return ResultStatus::NotFound;
	}
	else {
		return resultStatus;
	}
}

// Adds a new user to the file
ResultStatus UserTxtDataSource::AddNewUser(const UserModel& User) {
	try {
		FileTxtManager::SaveLineInFile(_ConverUserObjectToLine(User), FilePathes::USERS);
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Marks a user as deleted and saves the updated list
ResultStatus UserTxtDataSource::DeleteUser(const string& Username) {
	try {
		unique_ptr<vector<UserModel>> vUsers = make_unique<vector<UserModel>>();
		ResultStatus resultStatus = GetAllUsers(*vUsers);
		if (resultStatus == ResultStatus::Success)
		{
			for (UserModel& User : *vUsers) {
				if (_IsSameUsername(User.Username, Username))
				{
					User.MarkedForDelete = true;
					return _SaveUsers(*vUsers);
				}
			}
			return ResultStatus::NotFound;
		}
		else {
			return resultStatus;
		}
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Finds a user by username and returns it through reference
ResultStatus UserTxtDataSource::FindUserByUsername(UserModel& UserF, const string& Username) {
	unique_ptr<vector<UserModel>> vUsers = make_unique<vector<UserModel>>();
	ResultStatus resultStatus = GetAllUsers(*vUsers);
	if (resultStatus == ResultStatus::Failed) {
		return ResultStatus::Failed;
	}
	for (const UserModel& User : *vUsers) {
		if (_IsSameUsername(Username, User.Username)) {
			UserF = User;
			return ResultStatus::Found;
		}
	}
	return ResultStatus::NotFound;
}

// Loads all users from the text file into a vector
ResultStatus UserTxtDataSource::GetAllUsers(vector<UserModel>& vUsers) {
	try {
		unique_ptr<vector<string>> vContent = FileTxtManager::GetLinesFromFile(FilePathes::USERS);
		for (const string& line : *vContent)
		{
			vUsers.push_back(_ConvertLineToUserObject(line));
		}
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Singleton getter
UserTxtDataSource* UserTxtDataSource::getInstance() {
	if (_instance == nullptr) {
		_instance = unique_ptr<UserTxtDataSource>(new UserTxtDataSource());
	}
	return _instance.get();
}
