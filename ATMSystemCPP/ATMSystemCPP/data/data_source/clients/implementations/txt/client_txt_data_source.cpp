#include "client_txt_data_source.h"
#include "../../../../../core/constants/file_pathes/file_pathes.h"
#include "../../../../services/txt/file_txt_manager.h"
#include "../../../../../core/utils/headers/string_utils.h"
#include "../../../../../core/utils/headers/date_utils.h"
#include "../../../../../core/utils/headers/big_number_utils.h"
#include "../../../../../core/types/result_status.h"
#include "../../../../models/bank_client_model.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

// Singleton instance initialization
unique_ptr<ClientTxtDataSource> ClientTxtDataSource::_instance = nullptr;

// Constructor
ClientTxtDataSource::ClientTxtDataSource() {
}
// Converts a BankClientModel object to a line for file storage
string ClientTxtDataSource::_ConvertClientObjectToLine(const BankClientModel& Client, string Seperator) {
	string Line = Client.FirstName + Seperator + Client.LastName + Seperator + Client.Email + Seperator +
		Client.PhoneNumber + Seperator + Client.accountNumber + Seperator + Client.PinCode + Seperator +
		to_string(Client.GetAccountBalance());
	return Line;
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
ResultStatus ClientTxtDataSource::findClientByAccountNumber(BankClientModel& bankClientModel, const string& AccountNumber) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatus = getClients(*vClients);
	if (ResultStatus::Failed == resultStatus)
	{
		return ResultStatus::Failed;
	}
	else {
		for (const BankClientModel& Client : *vClients)
		{
			if (AccountNumber == Client.accountNumber) {
				bankClientModel = Client;
				return ResultStatus::Found;
			}
		}
		return ResultStatus::NotFound;
	}
}

// Updates an existing client's balance
ResultStatus ClientTxtDataSource::updateClientBalance(const BankClientModel& bankClientModel) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatus = getClients(*vClients);
	if (ResultStatus::Failed == resultStatus)
	{
		return ResultStatus::Failed;
	}
	else {
		for (BankClientModel& Client : *vClients)
		{
			if (Client.accountNumber == bankClientModel.accountNumber) {
				Client = bankClientModel;
				return _SaveClients(*vClients);
			}
		}
		return ResultStatus::NotFound;
	}
}



// Updates two clients in the file (used for transfers)
ResultStatus ClientTxtDataSource::updateBalanceTwoClients(const BankClientModel& firstClient, const BankClientModel& secondClient) {
	unique_ptr<vector<BankClientModel>> vClients = make_unique<vector<BankClientModel>>();
	ResultStatus resultStatusGetClients = getClients(*vClients);
	bool isFirstClientFound = false;
	bool isSecondClientFound = false;
	if (resultStatusGetClients == ResultStatus::Success)
	{
		for (size_t i = 0; i < vClients->size(); i++)
		{

			if (vClients->at(i).accountNumber == firstClient.accountNumber) {
				vClients->at(i) = firstClient;
				isFirstClientFound = true;
			}
			if (vClients->at(i).accountNumber == secondClient.accountNumber) {
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