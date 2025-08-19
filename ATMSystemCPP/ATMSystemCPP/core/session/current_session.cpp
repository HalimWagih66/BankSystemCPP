#include "current_session.h"
#include "../../data/models/bank_client_model.h"

std::unique_ptr<BankClientModel> CurrentSession::clientLogged = std::make_unique<BankClientModel>();
