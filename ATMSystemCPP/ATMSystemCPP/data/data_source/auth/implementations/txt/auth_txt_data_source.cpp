#include "../../../../../core/types/result_status.h"
#include "auth_txt_data_source.h"
#include <memory>
#include <vector>
#include "../../../../services/txt/file_txt_manager.h"
#include "../../../../../core/constants/file_pathes/file_pathes.h"
#include "../../../../../core/utils/headers/string_utils.h"
#include "../../../../../core/utils/headers/encryption.h"
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
BankClientModel AuthTxtDataSource::_ConvertLineToClientObject(string line, string Seperator)
{
	vector<string> vContent;
	vContent = StringUtils::SplitString(line, Seperator);

	return BankClientModel(vContent[0], vContent[1], vContent[2], vContent[3], vContent[4], vContent[5], stof(vContent[6]));
}

// Loads all clients from the file into the provided vector
ResultStatus AuthTxtDataSource::getAllClients(vector<BankClientModel>& vClients) {
	try {
		unique_ptr<vector<string>> vContent = FileTxtManager::GetLinesFromFile(FilePathes::CLIENTS);
		for (const string& line : *vContent)
		{
			vClients.push_back(_ConvertLineToClientObject(line));
		}
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}




// Attempts to log in a client by Account number and Pin code
ResultStatus AuthTxtDataSource::Login(const string& accountNumber,const string& pinCode, BankClientModel& bankClientModel) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatus = getAllClients(*vClients);
	if (resultStatus == ResultStatus::Success)
	{
		for (const BankClientModel& client : *vClients)
		{
			if (client.PinCode == pinCode && client.accountNumber == accountNumber) {
				bankClientModel = client;
				return ResultStatus::Success;
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
	*CurrentSession::clientLogged = BankClientModel();
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