#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../../../models/bank_client_model.h"
#include "../../../../core/types/result_status.h"

class IClientDataSource {
public:
    // Updates two clients in the file (used for transfers)
    virtual ResultStatus updateBalanceTwoClients(const BankClientModel& bankClientModel, const BankClientModel& otherBankClientModel) = 0;

    // Updates an existing client's balance
    virtual ResultStatus updateClientBalance(const BankClientModel& bankClientModel) = 0;

    // Finds a client by their account number
    virtual ResultStatus findClientByAccountNumber(BankClientModel& bankClientModel, const std::string& accountNumber) = 0;
};
