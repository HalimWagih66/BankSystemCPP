#pragma once
#include <string>
#include <vector>
#include "../../../../../core/types/result_status.h"
#include <memory>
#include "../../interface/interface_auth_data_source.h"
#include "../../../../models/bank_client_model.h"

class AuthTxtDataSource : public IAuthDataSource
{

    // Converts a client line to a Bank Client Model object
    BankClientModel _ConvertLineToClientObject(std::string line, std::string seperator = "#//#");

    // Loads all clients from the file into the provided vector
    ResultStatus getAllClients(std::vector<BankClientModel>& vClients);

    // Private constructor for singleton pattern
    AuthTxtDataSource();

    // Singleton instance pointer
    static std::unique_ptr<AuthTxtDataSource> _Instance;
public:
    // Logs out the current client
    ResultStatus Logout();

    // Attempts to log in a client and outputs the client object if found
    ResultStatus Login(const std::string& accountNumber,const std::string& pinCode, BankClientModel& outClient);

    // Returns the singleton instance of AuthTxtDataSource
    static AuthTxtDataSource* getInstance();
};