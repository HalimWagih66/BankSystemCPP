#pragma once
#include "../../../core/types/result_status.h"
#include <string>
#include <iostream>
using namespace std;
class UserUIHelpers
{
public:

    static void DisplayResultMessage(ResultStatus Result, string SuccessMessage = "Operation completed successfully.") {
        switch (Result) {
        case ResultStatus::Success:
            cout << "\n" << SuccessMessage<<"\n";
            break;
        case ResultStatus::NotFound:
            cout << "\nNo user found with this information.\n";
            break;
        case ResultStatus::AlreadyExists:
            cout << "\nUser already exists.\n";
            break;
        case ResultStatus::InvalidInput:
            cout << "\nInvalid input provided.\n";
            break;
        case ResultStatus::CancelledOperation:
            cout << "\nCancelled Operation By User\n";
            break;
        case ResultStatus::Failed:
        default:
            cout << "\nA problem occurred while extracting data.\n";
            break;
        }
    }

};

