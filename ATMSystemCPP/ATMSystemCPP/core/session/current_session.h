#pragma once
#include <memory>
#include "../../data/models/bank_client_model.h"
class CurrentSession {
public:
    static std::unique_ptr<BankClientModel> clientLogged;

    CurrentSession() = delete;
};
