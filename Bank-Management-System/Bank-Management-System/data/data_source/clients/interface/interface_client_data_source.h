#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../../../models/bank_client_model.h"
#include "../../../../core/types/result_status.h"
#include "../../../models/transfer_log_model.h"

class IClientDataSource {
protected:
    // Should generate a unique account number for a new client
    virtual ResultStatus _GenerateNextAccountNumber(std::string& AccountNumber) = 0;

public:
    // Updates two client records at once (e.g., during money transfer)
    virtual ResultStatus UpdateTwoClients(const BankClientModel& firstClient, const BankClientModel& secondClient) = 0;

    // Adds a new client to the data source
    virtual ResultStatus AddNewClient(BankClientModel& bankClientModel) = 0;

    // Updates an existing client in the data source
    virtual ResultStatus updateClient(const BankClientModel& bankClientModel) = 0;

    // Deletes a client by account number
    virtual ResultStatus deleteClient(const std::string& AccountNumber) = 0;

    // Saves a money transfer log record to the data source
    virtual ResultStatus RegisterTransferLog(const TransferLogModel& TrnsferLogRecord) = 0;

    // Retrieves all transfer logs
    virtual ResultStatus GetRegisterTransferLogs(std::vector<TransferLogModel>& vTrnsferLogRecord) = 0;

    // Retrieves all clients from the data source
    virtual ResultStatus getClients(std::vector<BankClientModel>& outClients) = 0;

    // Finds a client by their account number
    virtual ResultStatus FindClientByAccountNumber(BankClientModel& bankClientModel, const std::string& _AccountNumber) = 0;
};
