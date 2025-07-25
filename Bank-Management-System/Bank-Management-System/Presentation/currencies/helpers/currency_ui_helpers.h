#pragma once
#include "../../core/types/result_status.h"
#include <iostream>
class CurrenciesUIHelpers {
public:

    static void DisplayResultMessage(ResultStatus Result, std::string SuccessMessage = "Operation completed successfully.") {
        switch (Result) {
        case ResultStatus::Success:
            std::cout << SuccessMessage;
            break;
        case ResultStatus::NotFound:
            std::cout << "\nNo Currency found with this information.\n";
            break;
        case ResultStatus::AlreadyExists:
            std::cout << "\Currency already exists.\n";
            break;
        case ResultStatus::InvalidInput:
            std::cout << "\nInvalid input provided.\n";
            break;
        case ResultStatus::CancelledOperation:
            std::cout << "\nCancelled Operation By User\n";
            break;
        case ResultStatus::Failed:
        default:
            std::cout << "\nA problem occurred while extracting data.\n";
            break;
        }
    }

};