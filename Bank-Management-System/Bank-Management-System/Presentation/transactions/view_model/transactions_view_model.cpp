#include "transactions_view_model.h"
#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../../../core/types/result_status.h"
#include "../../../data/models/bank_client_model.h"
#include "../../../data/models/transfer_log_model.h"
#include <memory>
#include <vector>
#include <string>
#include "../../../core/utils/headers/date_utils.h"
#include "../../../core/session/current_session.h"

using namespace std;

// Initialize the singleton instance of TransactionsViewModel
unique_ptr<TransactionsViewModel> TransactionsViewModel::_instance = nullptr;

// Private constructor that accepts the client data source
TransactionsViewModel::TransactionsViewModel(IClientDataSource* dataSource) {
    _dataSource = dataSource;
}

// Singleton accessor - creates an instance if not already created
TransactionsViewModel* TransactionsViewModel::getInstance(IClientDataSource* dataSource) {
    if (_instance == nullptr) {
        _instance = unique_ptr<TransactionsViewModel>(new TransactionsViewModel(dataSource));
    }
    return _instance.get();
}

// Fetches all clients from the data source and stores them in outClients
ResultStatus TransactionsViewModel::getClients(std::vector<BankClientModel>& outClients)
{
    unique_ptr<vector<BankClientModel>> vBankClientModel = make_unique<vector<BankClientModel>>();
    ResultStatus resultStatus = _dataSource->getClients(*vBankClientModel);
    if (resultStatus == ResultStatus::Success) {
        outClients = move(*vBankClientModel);
    }
    return resultStatus;
}

// Searches for a client by account number
ResultStatus TransactionsViewModel::searchClient(BankClientModel& bankClientModel, const std::string& accountNumber)
{
    return _dataSource->FindClientByAccountNumber(bankClientModel, accountNumber);
}

// Updates a client's data
ResultStatus TransactionsViewModel::updateClient(const BankClientModel& client)
{
    return _dataSource->updateClient(client);
}

// Transfers money between two clients and registers the transfer log if successful
ResultStatus TransactionsViewModel::transferMoney(BankClientModel& sender, BankClientModel& receiver, const double& amount)
{
    sender.accountBalance -= amount;
    receiver.accountBalance += amount;

    ResultStatus resultStatusUpdate = _dataSource->UpdateTwoClients(sender, receiver);

    if (resultStatusUpdate == ResultStatus::Success)
    {
        // Log the transfer after successful update
        return RegisterTransferLog(sender, receiver, amount);
    }

    return resultStatusUpdate;
}

// Withdraws money from a client's account
ResultStatus TransactionsViewModel::withdrawMoney(BankClientModel& client, const double& amount)
{
    client.accountBalance -= amount;
    return updateClient(client);
}

// Deposits money into a client's account
ResultStatus TransactionsViewModel::depositMoney(BankClientModel& client, const double& amount)
{
    client.accountBalance += amount;
    return updateClient(client);
}

// Retrieves all transfer logs and stores them in the output vector
ResultStatus TransactionsViewModel::getTransferLogs(vector<TransferLogModel>& outListOfTransferLogModel)
{
    unique_ptr<vector<TransferLogModel>> vTransferLogModel = make_unique<vector<TransferLogModel>>();
    ResultStatus resultStatus = _dataSource->GetRegisterTransferLogs(*vTransferLogModel);
    if (resultStatus == ResultStatus::Success)
    {
        outListOfTransferLogModel = move(*vTransferLogModel);
    }
    return resultStatus;
}

// Creates and saves a transfer log for a transaction between two clients
ResultStatus TransactionsViewModel::RegisterTransferLog(const BankClientModel& sender, const BankClientModel& receiver, const double& amount)
{
    unique_ptr<TransferLogModel> transferLogModel = make_unique<TransferLogModel>();

    transferLogModel->sourceAccountNumber = sender.accountNumber;
    transferLogModel->destinationAccountNumber = receiver.accountNumber;
    transferLogModel->amount = amount;
    transferLogModel->dateTime = DateUtils::GetSystemDateTimeString();
    transferLogModel->srcBalanceAfter = sender.accountBalance;
    transferLogModel->destBalanceAfter = receiver.accountBalance;
    transferLogModel->Username = CurrentSession::UserLogged->Username;

    return _dataSource->RegisterTransferLog(*transferLogModel);
}
