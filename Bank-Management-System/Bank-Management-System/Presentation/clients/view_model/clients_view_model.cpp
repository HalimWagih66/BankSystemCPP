#include "clients_view_model.h"
#include <string>
#include <vector>
#include "../../../data/models/bank_client_model.h"
#include <memory>
#include "../../../core/types/result_status.h"

using namespace std;

// Initialize the singleton instance to nullptr
unique_ptr<ClientsViewModel> ClientsViewModel::_instance = nullptr;

// Private constructor: initializes the ViewModel with a client data source
ClientsViewModel::ClientsViewModel(IClientDataSource* clientDataSource) {
    _clientDataSource = clientDataSource;
}

// Searches for a client using the account number
// If found, fills the passed BankClientModel reference with the client's data
ResultStatus ClientsViewModel::searchClient(BankClientModel& bankClientModel, const std::string& accountNumber)
{
    ResultStatus resultStatus = _clientDataSource->FindClientByAccountNumber(bankClientModel, accountNumber);
    return resultStatus;
}

// Updates a client's data
ResultStatus ClientsViewModel::updateClient(const BankClientModel& client)
{
    return _clientDataSource->updateClient(client);
}

// Retrieves all clients and stores them in the provided vector
ResultStatus ClientsViewModel::getAllClients(vector<BankClientModel>& clients)
{
    return _clientDataSource->getClients(clients);
}

// Adds a new client
ResultStatus ClientsViewModel::addNewClient(BankClientModel& client)
{
    return _clientDataSource->AddNewClient(client);
}

// Deletes a client by their account number
ResultStatus ClientsViewModel::deleteClient(const string& accountNumber)
{
    return _clientDataSource->deleteClient(accountNumber);
}

// Returns the singleton instance of ClientsViewModel
// Creates one if it doesn't exist, injecting the data source dependency
ClientsViewModel* ClientsViewModel::getInstance(IClientDataSource* clientDataSource) {
    if (_instance == nullptr)
    {
        _instance = unique_ptr<ClientsViewModel>(new ClientsViewModel(clientDataSource));
    }
    return _instance.get();
}
