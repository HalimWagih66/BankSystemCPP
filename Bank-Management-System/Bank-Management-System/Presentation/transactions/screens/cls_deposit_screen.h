#pragma once
#include <iostream>
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../../data/models/bank_client_model.h"
#include "../../../Presentation/transactions/view_model/transactions_view_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include "../../../core/types/result_status.h"
#include "../../base/base_screen.h"
#include "../../clients/helpers/client_ui_helpers.h"
#include <string>
class clsDepositScreen : public BaseScreen {
private:
	static void _ProccessDeposit(BankClientModel& bankClientModel, TransactionsViewModel* transactionsViewModel) {
		bankClientModel.PrintInfo();
		float amount = DataReader::PromptAndReadFloatNumberBetween(5,1000000,"Please Enter deposit amount : ","Please Enter deposit amount from 5 EGP to 1000000 EGP : ");
		if (DataReader::AreYouSure("Are you sure you want to perform this transaction [Y/N] : "))
		{
			ResultStatus resultStatus = transactionsViewModel->depositMoney(bankClientModel,amount);
			if (resultStatus == ResultStatus::Success) {
				std::cout << "\n\nAmount Deposited Successfully.\n\n";
				std::cout << "\n\nNew Balance Is: " << bankClientModel.accountBalance << "\n\n";
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
	static void ShowDepositScreen(TransactionsViewModel* transactionsViewModel) {

		_DrawScreenHeader("\t  Deposit Screen");

		std::cout << "Please Enter the Account Number of the Client to Deposit: \n";

		std::string accountNumber = DataReader::ReadAccountNumber();

		std::unique_ptr<BankClientModel> bankClientModel = std::make_unique<BankClientModel>();

		ResultStatus resultStatus = transactionsViewModel->searchClient(*bankClientModel, accountNumber);

		if (resultStatus == ResultStatus::Found)
		{
			_ProccessDeposit(*bankClientModel, transactionsViewModel);
		}
		else {
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};