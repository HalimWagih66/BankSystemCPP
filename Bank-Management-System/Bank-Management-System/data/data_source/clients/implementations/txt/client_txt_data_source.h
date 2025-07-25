#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../../../../models/bank_client_model.h"
#include "../../../../models/transfer_log_model.h"
#include "../../interface/interface_client_data_source.h"
#include "../../../../../core/types/result_status.h"

class ClientTxtDataSource : public IClientDataSource
{
private:
    // Generates the next unique account number for new clients
    ResultStatus _GenerateNextAccountNumber(std::string& AccountNumber);

    // Converts a BankClientModel object to a line of text for file storage
    std::string _ConvertClientObjectToLine(const BankClientModel& Client, std::string Seperator = "#//#");

    // Converts a TransferLogModel object to a line of text for file storage
    std::string _PrepareTransferLogRecord(TransferLogModel TransferLog, std::string seperator = "#//#");

    // Parses a line of text into a TransferLogModel object
    TransferLogModel _TransferRegisterObjectFromLine(std::string line, std::string seperator = "#//#");

    // Parses a line of text into a BankClientModel object
    BankClientModel _ConverLineToClientObject(const std::string& Line, std::string Seperator = "#//#");

    // Saves the given clients vector to the file
    ResultStatus _SaveClients(const std::vector<BankClientModel>& vClients);

    // Compares two account numbers after trimming and formatting
    bool _IsSameAccountNumber(const std::string& AccountNumber, const std::string& AccountNumber2);

    // Private constructor for singleton pattern
    ClientTxtDataSource();

    // Singleton instance
    static std::unique_ptr<ClientTxtDataSource> _instance;

public:
    // Updates the data of two clients at once (e.g., after transfer)
    ResultStatus UpdateTwoClients(const BankClientModel& firstClient, const BankClientModel& secondClient);

    // Retrieves all clients from the file
    ResultStatus getClients(std::vector<BankClientModel>& vClients);

    // Adds a new client to the file
    ResultStatus AddNewClient(BankClientModel& bankClientModel);

    // Searches for a client by their account number
    ResultStatus FindClientByAccountNumber(BankClientModel& bankClientModel, const std::string& AccountNumber);

    // Updates an existing client's data
    ResultStatus updateClient(const BankClientModel& bankClientModel);

    // Marks a client as deleted using their account number
    ResultStatus deleteClient(const std::string& AccountNumber);

    // Saves updates to a list of clients
    ResultStatus UpdateClients(std::vector<BankClientModel>& vClients);

    // Retrieves all transfer logs from file
    ResultStatus GetRegisterTransferLogs(std::vector<TransferLogModel>& vTrnsferLogRecord);

    // Registers (saves) a new transfer log entry
    ResultStatus RegisterTransferLog(const TransferLogModel& TrnsferLogRecord);

    // Returns the singleton instance of this class
    static ClientTxtDataSource* getInstance();
};
