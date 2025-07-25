#include "view_model_provider.h"
#include "../../data/data_source/clients/implementations/txt/client_txt_data_source.h"
#include "../../Presentation/clients/view_model/clients_view_model.h"
#include "../../Presentation/auth/view_model/auth_view_model.h"
#include "../../data/data_source/auth/implementations/txt/auth_txt_data_source.h"
#include "../../Presentation/users/view_model/users_view_model.h"
#include "../../data/data_source/users/implementations/txt/user_txt_data_source.h"
#include "../../data/data_source/currencies/implementations/txt/currencies_txt_data_source.h"
#include "../../Presentation/currencies/view_model/currencies_view_model.h"
// Provides the singleton instance of ClientsViewModel using the singleton data source
ClientsViewModel* ViewModelProvider::getClientsViewModel()
{
    return ClientsViewModel::getInstance(ClientTxtDataSource::getInstance());
}

// Provides the singleton instance of AuthViewModel using the singleton data source
AuthViewModel* ViewModelProvider::getAuthViewModel()
{
    return AuthViewModel::getInstance(AuthTxtDataSource::getInstance());
}

// Provides the singleton instance of UsersViewModel using the singleton data source
UsersViewModel* ViewModelProvider::getUsersViewModel()
{
    return UsersViewModel::getInstance(UserTxtDataSource::getInstance());
}

// Provides the singleton instance of TransactionsViewModel using the same data source used by Clients
TransactionsViewModel* ViewModelProvider::getTransactionsViewModel()
{
    return TransactionsViewModel::getInstance(ClientTxtDataSource::getInstance());
}

// Provides the singleton instance of CurrenciesViewModel using the singleton data source
CurrenciesViewModel* ViewModelProvider::getCurrenciesViewModel()
{
    return CurrenciesViewModel::getInstance(CurrenciesTxtDataSource::getInstance());
}
