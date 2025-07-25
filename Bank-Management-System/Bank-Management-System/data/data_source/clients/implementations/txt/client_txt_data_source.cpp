#include "client_txt_data_source.h"
#include "../../../../../core/constants/file_pathes/file_pathes.h"
#include "../../../../services/txt/file_txt_manager.h"
#include "../../../../../core/utils/headers/string_utils.h"
#include "../../../../../core/utils/headers/date_utils.h"
#include "../../../../../core/utils/headers/big_number_utils.h"
#include "../../../../../core/types/result_status.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

// Singleton instance initialization
unique_ptr<ClientTxtDataSource> ClientTxtDataSource::_instance = nullptr;

// Constructor
ClientTxtDataSource::ClientTxtDataSource() {
}

// Generates the next available account number for a new client
ResultStatus ClientTxtDataSource::_GenerateNextAccountNumber(string& AccountNumber) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatus = getClients(*vClients);
	if (resultStatus == ResultStatus::Success)
	{
		if (vClients->empty()) {
			AccountNumber = "0000000001";
			return ResultStatus::Success;
		}

		string lastAccountNumber = vClients->back().GetAccountNumber();

		AccountNumber = BigNumberUtils::IncrementByOne(lastAccountNumber);
		return ResultStatus::Success;
	}
	else
	{
		throw runtime_error("There was a problem while extracting the account number.");
	}
}

// Converts a BankClientModel object to a line for file storage
string ClientTxtDataSource::_ConvertClientObjectToLine(const BankClientModel& Client, string Seperator) {
	string Line = Client.FirstName + Seperator + Client.LastName + Seperator + Client.Email + Seperator +
		Client.PhoneNumber + Seperator + Client.accountNumber + Seperator + Client.PinCode + Seperator +
		to_string(Client.GetAccountBalance());
	return Line;
}

// Prepares a transfer log record as a string for file storage
string ClientTxtDataSource::_PrepareTransferLogRecord(TransferLogModel TransferLog, string seperator) {
	string transferRecord = "";
	transferRecord = DateUtils::GetSystemDateTimeString() + seperator;
	transferRecord += TransferLog.sourceAccountNumber + seperator;
	transferRecord += TransferLog.destinationAccountNumber + seperator;
	transferRecord += to_string(TransferLog.amount) + seperator;
	transferRecord += to_string(TransferLog.srcBalanceAfter) + seperator;
	transferRecord += to_string(TransferLog.destBalanceAfter) + seperator;
	transferRecord += TransferLog.Username;
	return transferRecord;
}

// Converts a line from the transfer log file to a TransferLogModel object
TransferLogModel ClientTxtDataSource::_TransferRegisterObjectFromLine(string line, string seperator) {
	vector<string> vContect = StringUtils::SplitString(line, seperator);
	TransferLogModel TransferLog;
	TransferLog.dateTime = vContect[0];
	TransferLog.sourceAccountNumber = vContect[1];
	TransferLog.destinationAccountNumber = vContect[2];
	TransferLog.amount = stof(vContect[3]);
	TransferLog.srcBalanceAfter = stof(vContect[4]);
	TransferLog.destBalanceAfter = stof(vContect[5]);
	TransferLog.Username = vContect[6];
	return TransferLog;
}

// Converts a line from the client file to a BankClientModel object
BankClientModel ClientTxtDataSource::_ConverLineToClientObject(const string& Line, string Seperator) {
	vector <string> vContent = StringUtils::SplitString(Line, Seperator);

	return BankClientModel(vContent[0], vContent[1], vContent[2], vContent[3], vContent[4], vContent[5], stof(vContent[6]));
}

// Saves all clients to the file, skipping those marked for deletion
ResultStatus ClientTxtDataSource::_SaveClients(const vector<BankClientModel>& vClients) {
	vector<string> vClientsString;
	for (const BankClientModel& Client : vClients)
	{
		if (Client.GetMarkedForDelete() == false)
		{
			vClientsString.push_back(_ConvertClientObjectToLine(Client));
		}
	}
	try {
		FileTxtManager::SaveLinesInFile(vClientsString, FilePathes::CLIENTS);
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Compares two account numbers for equality (case-insensitive, trimmed)
bool ClientTxtDataSource::_IsSameAccountNumber(const string& AccountNumber, const string& AccountNumber2) {
	return (StringUtils::ToUpperCase(StringUtils::TrimString(AccountNumber)) == StringUtils::ToUpperCase(StringUtils::TrimString(AccountNumber2)));
}

// Loads all clients from the file into the provided vector
ResultStatus ClientTxtDataSource::getClients(vector<BankClientModel>& vClients) {
	try {
		unique_ptr<vector<string>> vContent = FileTxtManager::GetLinesFromFile(FilePathes::CLIENTS);
		for (const string& line : *vContent)
		{
			vClients.push_back(_ConverLineToClientObject(line));
		}
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Finds a client by account number and outputs the client object if found
ResultStatus ClientTxtDataSource::FindClientByAccountNumber(BankClientModel& bankClientModel, const string& AccountNumber) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatus = getClients(*vClients);
	if (ResultStatus::Failed == resultStatus)
	{
		return ResultStatus::Failed;
	}
	else {
		for (const BankClientModel& Client : *vClients)
		{
			if (_IsSameAccountNumber(AccountNumber, Client.accountNumber)) {
				bankClientModel = Client;
				return ResultStatus::Found;
			}
		}
		return ResultStatus::NotFound;
	}
}

// Adds a new client to the file
ResultStatus ClientTxtDataSource::AddNewClient(BankClientModel& bankClientModel) {
	try {
		string AccountNumber;
		ResultStatus resultStatus = _GenerateNextAccountNumber(AccountNumber);
		if (resultStatus == ResultStatus::Success)
		{
			bankClientModel.accountNumber = AccountNumber;
			FileTxtManager::SaveLineInFile(_ConvertClientObjectToLine(bankClientModel), FilePathes::CLIENTS);
			return ResultStatus::Success;
		}
		return resultStatus;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Updates an existing client in the file
ResultStatus ClientTxtDataSource::updateClient(const BankClientModel& bankClientModel) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatus = getClients(*vClients);
	if (ResultStatus::Failed == resultStatus)
	{
		return ResultStatus::Failed;
	}
	else {
		for (BankClientModel& Client : *vClients)
		{
			if (_IsSameAccountNumber(Client.accountNumber, bankClientModel.accountNumber)) {
				Client = bankClientModel;
				return _SaveClients(*vClients);
			}
		}
		return ResultStatus::NotFound;
	}
}

// Deletes a client by marking for deletion and saving the updated list
ResultStatus ClientTxtDataSource::deleteClient(const string& AccountNumber) {
	try {
		unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
		ResultStatus resultStatus = getClients(*vClients);
		if (resultStatus == ResultStatus::Success)
		{
			for (BankClientModel& bankClientModel : *vClients) {
				if (_IsSameAccountNumber(AccountNumber, bankClientModel.accountNumber))
				{
					bankClientModel.SetMarkedForDelete(true);
					ResultStatus resultStatus = _SaveClients(*vClients);
					return resultStatus;
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

// Updates all clients in the file
ResultStatus ClientTxtDataSource::UpdateClients(vector<BankClientModel>& vClients) {
	return _SaveClients(vClients);
}

// Loads all transfer logs from the file into the provided vector
ResultStatus ClientTxtDataSource::GetRegisterTransferLogs(vector<TransferLogModel>& vTrnsferLogRecord) {
	try {
		unique_ptr<vector<string>> vContent = FileTxtManager::GetLinesFromFile(FilePathes::TransferHistory);
		for (const string& line : *vContent)
		{
			vTrnsferLogRecord.push_back(_TransferRegisterObjectFromLine(line));
		}
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Saves a transfer log record to the file
ResultStatus ClientTxtDataSource::RegisterTransferLog(const TransferLogModel& TrnsferLogRecord) {
	try {
		FileTxtManager::SaveLineInFile(_PrepareTransferLogRecord(TrnsferLogRecord), FilePathes::TransferHistory);
		return ResultStatus::Success;
	}
	catch (...) {
		return ResultStatus::Failed;
	}
}

// Updates two clients in the file (used for transfers)
ResultStatus ClientTxtDataSource::UpdateTwoClients(const BankClientModel& firstClient, const BankClientModel& secondClient) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatusGetClients = getClients(*vClients);
	bool isFirstClientFound = false;
	bool isSecondClientFound = false;
	if (resultStatusGetClients == ResultStatus::Success)
	{
		for (size_t i = 0; i < vClients->size(); i++)
		{

			if (_IsSameAccountNumber(vClients->at(i).accountNumber, firstClient.accountNumber)) {
				vClients->at(i) = firstClient;
				isFirstClientFound = true;
			}
			if (_IsSameAccountNumber(vClients->at(i).accountNumber, secondClient.accountNumber)) {
				vClients->at(i) = secondClient;
				isSecondClientFound = true;
			}
			if (isFirstClientFound && isSecondClientFound)
			{
				return _SaveClients(*vClients);
			}
		}
	}
	return resultStatusGetClients;
}

// Returns the singleton instance of ClientTxtDataSource
ClientTxtDataSource* ClientTxtDataSource::getInstance()
{
	if (_instance == nullptr) {
		_instance = unique_ptr<ClientTxtDataSource>(new ClientTxtDataSource());
	}
	return _instance.get();
}