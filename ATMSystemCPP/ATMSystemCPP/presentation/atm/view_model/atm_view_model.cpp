#include "atm_view_model.h"
#include <memory>
#include "../../../core/types/result_status.h"
#include "../../../data/models/bank_client_model.h"
#include "../../../data/data_source/clients/interface/interface_client_data_source.h"

#include "../../../core/session/current_session.h"
std::unique_ptr<ATMViewModel> ATMViewModel::_instance = nullptr;

ATMViewModel::ATMViewModel(IClientDataSource* clientDataSource) : _dataSource(clientDataSource){}
ResultStatus ATMViewModel::withdrawAmount(int amount)
{
	CurrentSession::clientLogged->SetAccountBalance(CurrentSession::clientLogged->accountBalance - amount);
	return _dataSource->updateClientBalance(*CurrentSession::clientLogged);
}
ResultStatus ATMViewModel::depositAmount(int amount)
{
	CurrentSession::clientLogged->SetAccountBalance(CurrentSession::clientLogged->accountBalance + amount);
	return _dataSource->updateClientBalance(*CurrentSession::clientLogged);
}
ResultStatus ATMViewModel::transferAmount(int amount, BankClientModel& sourceClient, BankClientModel& destinationClient)
{
	sourceClient.accountBalance -= amount;
	destinationClient.accountBalance += amount;
	return _dataSource->updateBalanceTwoClients(sourceClient,destinationClient);
}
ATMViewModel* ATMViewModel::getInstance(IClientDataSource* clientDataSource) {
	if (_instance == NULL)
	{
		_instance = std::unique_ptr<ATMViewModel>(new ATMViewModel(clientDataSource));
	}
	return _instance.get();
}