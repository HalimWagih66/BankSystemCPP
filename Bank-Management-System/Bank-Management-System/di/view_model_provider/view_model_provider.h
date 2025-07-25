#pragma once
#include "../../Presentation/clients/view_model/clients_view_model.h"
#include "../../Presentation/users/view_model/users_view_model.h"
#include "../../Presentation/auth/view_model/auth_view_model.h"
#include "../../Presentation/transactions/view_model/transactions_view_model.h"
#include "../../Presentation/currencies/view_model/currencies_view_model.h"
class ViewModelProvider
{
public:
    // Returns a singleton instance of ClientsViewModel
    static ClientsViewModel* getClientsViewModel();

    // Returns a singleton instance of AuthViewModel
    static AuthViewModel* getAuthViewModel();

    // Returns a singleton instance of UsersViewModel
    static UsersViewModel* getUsersViewModel();

    // Returns a singleton instance of TransactionsViewModel
    static TransactionsViewModel* getTransactionsViewModel();

    // Returns a singleton instance of CurrenciesViewModel
    static CurrenciesViewModel* getCurrenciesViewModel();
};


