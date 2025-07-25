#pragma once

#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../../../core/types/result_status.h"
#include "../../../data/models/bank_client_model.h"
#include "../../../data/models/transfer_log_model.h"
#include <memory>
#include <string>
#include <vector>

// ViewModel responsible for managing money transactions and logs between clients
class TransactionsViewModel
{
    // Singleton instance of the ViewModel
    static std::unique_ptr<TransactionsViewModel> _instance;

    // Pointer to the data source interface for performing client-related operations
    IClientDataSource* _dataSource;

    // Private constructor to enforce singleton pattern
    TransactionsViewModel(IClientDataSource* dataSource);

public:
    // Returns the singleton instance of TransactionsViewModel
    // Creates a new one if it doesn't exist yet
    static TransactionsViewModel* getInstance(IClientDataSource* dataSource);

    // Retrieves all clients and stores them in the provided vector
    ResultStatus getClients(std::vector<BankClientModel>& outClients);

    // Searches for a client by account number and fills the provided BankClientModel if found
    ResultStatus searchClient(BankClientModel& bankClientModel, const std::string& accountNumber);

    // Updates the given client's data
    ResultStatus updateClient(const BankClientModel& client);

    // Transfers money from the sender to the receiver and logs the transaction
    ResultStatus transferMoney(BankClientModel& sender, BankClientModel& receiver, const double& amount);

    // Withdraws money from a client's account
    ResultStatus withdrawMoney(BankClientModel& client, const double& amount);

    // Deposits money into a client's account
    ResultStatus depositMoney(BankClientModel& client, const double& amount);

    // Retrieves all transfer logs and stores them in the provided vector
    ResultStatus getTransferLogs(std::vector<TransferLogModel>& TransferLogModel);

    // Registers a money transfer log entry
    ResultStatus RegisterTransferLog(const BankClientModel& sender, const BankClientModel& receiver, const double& amount);
};
