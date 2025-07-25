#pragma once

#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include <vector>
#include <string>
#include <memory>

// ViewModel responsible for managing client-related operations
class ClientsViewModel
{
private:
    // Data source abstraction for client data operations (injected via constructor)
    IClientDataSource* _clientDataSource;

    // Singleton instance of ClientsViewModel
    static std::unique_ptr<ClientsViewModel> _instance;

    // Private constructor to enforce singleton pattern
    ClientsViewModel(IClientDataSource* clientDataSource);

public:
    // Searches for a client using the account number
    // If found, fills bankClientModel with the result
    ResultStatus searchClient(BankClientModel& bankClientModel, const std::string& accountNumber);

    // Updates the given client's data
    ResultStatus updateClient(const BankClientModel& client);

    // Retrieves all clients and stores them in the provided vector
    ResultStatus getAllClients(std::vector<BankClientModel>& clients);

    // Adds a new client using the provided client model
    ResultStatus addNewClient(BankClientModel& client);

    // Deletes a client based on their account number
    ResultStatus deleteClient(const std::string& accountNumber);

    // Returns the singleton instance of the ClientsViewModel
    // Initializes the instance with the provided data source if not already created
    static ClientsViewModel* getInstance(IClientDataSource* clientDataSource);
};
