#pragma once
#include <iomanip>
#include <sstream>
#include "../view_model/transactions_view_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include "../../base/base_screen.h"
#include "../../../core/types/result_status.h"
#include "../../../data/models/bank_client_model.h"
#include "../../clients/helpers/client_ui_helpers.h"
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
using namespace std;
class clsWithdrawScreen : protected BaseScreen
{
	static void _ProccessWithdraw(BankClientModel& bankClientModel,TransactionsViewModel* transactionsViewModel) {
		ostringstream oss;
		oss << fixed << setprecision(2);
		
		bankClientModel.PrintInfo();
		cout << "\n\n";
		float amount = DataReader::PromptAndReadFloatNumberBetween(5, bankClientModel.accountBalance, "Please Enter withdraw amount : ", "Please Enter withdraw amount from 5 EGP to "+to_string(bankClientModel.accountBalance) + " EGP : ");
		cout << "\n\n";
		if (DataReader::AreYouSure("Are you sure you want to perform this transaction [Y/N] : "))
		{
			ResultStatus resultStatus = transactionsViewModel->withdrawMoney(bankClientModel, amount);
			if (resultStatus == ResultStatus::Success) {
				std::cout << "\nAmount Withdraw Successfully.\n";
				std::cout << "\nNew Balance Is: " << bankClientModel.accountBalance << endl;
			}
			else
			{
				ClientUIHelpers::DisplayResultMessage(resultStatus);
			}
		}
		else
		{
			std::cout << "\nOperation was cancelled.\n";
		}
	}

public:
	static void ShowWithdrawScreen(TransactionsViewModel* transactionsViewModel) {
		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNumber = DataReader::ReadAccountNumber("Please Enter the Account Number of the Client to Withdraw: ");

		std::unique_ptr<BankClientModel> bankClientModel = std::make_unique<BankClientModel>();

		ResultStatus resultStatus = transactionsViewModel->searchClient(*bankClientModel, AccountNumber);

		if (resultStatus == ResultStatus::Found)
		{
			_ProccessWithdraw(*bankClientModel, transactionsViewModel);
		}
		else {
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};

