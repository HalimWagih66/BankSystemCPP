#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../../../../models/bank_client_model.h"
#include "../../interface/interface_client_data_source.h"
#include "../../../../../core/types/result_status.h"

class ClientTxtDataSource : public IClientDataSource
{
private:

	static std::unique_ptr<ClientTxtDataSource> _instance;

	ResultStatus _SaveClients(const std::vector<BankClientModel>& vClients);

	ResultStatus getClients(std::vector<BankClientModel>& vClients);

	BankClientModel _ConverLineToClientObject(const std::string& Line, std::string Seperator = "#//#");

	std::string _ConvertClientObjectToLine(const BankClientModel& Client, std::string Seperator = "#//#");
public:

	ClientTxtDataSource();

	ResultStatus findClientByAccountNumber(BankClientModel& bankClientModel, const std::string& accountNumber);

	ResultStatus updateClientBalance(const BankClientModel& bankClientModel);

	ResultStatus updateBalanceTwoClients(const BankClientModel& firstClient, const BankClientModel& secondClient);

	static ClientTxtDataSource* getInstance();
};
