#include "../../../../../core/types/result_status.h"
#include "auth_txt_data_source.h"
#include <memory>
#include <vector>
#include "../../../../services/txt/file_txt_manager.h"
#include "../../../../../core/constants/file_pathes/file_pathes.h"
#include "../../../../../core/utils/headers/string_utils.h"
#include "../../../../../core/utils/headers/encryption.h"
#include "../../../../models/login_register_model.h"
#include <string>
#include "../../../../../core/utils/headers/date_utils.h"
#include "../../../../../core/session/current_session.h"

using namespace std;
// Singleton instance initialization
unique_ptr<AuthTxtDataSource> AuthTxtDataSource::_Instance = nullptr;

// Constructor
AuthTxtDataSource::AuthTxtDataSource() {
	// Constructor implementation if needed
}

// Converts a line from the file into a UserModel object
UserModel AuthTxtDataSource::_ConvertLineToUserObject(string line, string Seperator)
{
	vector<string> vUserData;
	vUserData = StringUtils::SplitString(line, Seperator);

	return UserModel(vUserData[0], vUserData[1], vUserData[2],
		vUserData[3], vUserData[4], Encryption::DecryptText(vUserData[5]), stoi(vUserData[6]));
}

// Loads all users from the file into a vector
ResultStatus AuthTxtDataSource::_GetAllUsers(vector<UserModel>& vUsers) {
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

// Prepares a login record string for saving to file
string AuthTxtDataSource::_PrepareLoginRecord(LoginRegisterModel LoginRegisterRecord, string seperator) {
	string LoginRecord = "";
	LoginRecord += DateUtils::GetSystemDateTimeString() + seperator;
	LoginRecord += LoginRegisterRecord.Username + seperator;
	LoginRecord += Encryption::EncryptText(LoginRegisterRecord.Password) + seperator;
	LoginRecord += to_string(LoginRegisterRecord.Permissions);
	return LoginRecord;
}

// Converts a line from the login log file into a LoginRegisterModel object
LoginRegisterModel AuthTxtDataSource::_ConvertLineToRegisterRecord(string line, string seperator) {
	LoginRegisterModel registerModel;
	vector<string> vContent = StringUtils::SplitString(line, seperator);
	registerModel.DateTime = vContent[0];
	registerModel.Username = vContent[1];
	registerModel.Password = Encryption::DecryptText(vContent[2]);
	registerModel.Permissions = stoi(vContent[3]);
	return registerModel;
}

// Loads all login/register logs from the file into a vector
ResultStatus AuthTxtDataSource::GetRegisterLoginLogs(vector<LoginRegisterModel>& vLoginRegisterRecords) {
	try {
		unique_ptr<vector<string>> vContent = FileTxtManager::GetLinesFromFile(FilePathes::LoginActivityTracker);
		for (const string& line : *vContent)
		{
			vLoginRegisterRecords.push_back(_ConvertLineToRegisterRecord(line));
		}
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Saves a login/register log record to the file
ResultStatus AuthTxtDataSource::RegisterLoginLog(const LoginRegisterModel& loginRegisterRecord)
{
	try {
		FileTxtManager::SaveLineInFile(_PrepareLoginRecord(loginRegisterRecord), FilePathes::LoginActivityTracker);
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Attempts to log in a user by username and password
ResultStatus AuthTxtDataSource::LoginUser(const string& Username, const string& Password, UserModel& outUser) {
	unique_ptr<vector<UserModel>> vUsers = unique_ptr<vector<UserModel>>();
	ResultStatus resultStatus = _GetAllUsers(*vUsers);
	if (resultStatus == ResultStatus::Success)
	{
		for (const UserModel& User : *vUsers)
		{
			if (User.Username == Username && User.Password == Password) {
				outUser = User;
				return ResultStatus::Found;
			}
		}
		return ResultStatus::NotFound;
	}
	else {
		return resultStatus;
	}
}

// Logs out the current user by resetting the session
ResultStatus AuthTxtDataSource::Logout()
{
	*CurrentSession::UserLogged = UserModel();
	return ResultStatus::Success;
}

// Returns the singleton instance of AuthTxtDataSource
AuthTxtDataSource* AuthTxtDataSource::getInstance() {
	if (_Instance == nullptr)
	{
		_Instance = unique_ptr<AuthTxtDataSource>(new AuthTxtDataSource());
	}
	return _Instance.get();
}