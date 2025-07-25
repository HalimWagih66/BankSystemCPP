#pragma once
#include "../../data/models/bank_client_model.h"
#include "../../../core/types/result_status.h"
#include <iostream>
#include <memory>
#include "../../../core/utils/headers/data_reader.h"
#include <string>
#include "../../../data/models/transfer_log_model.h"
#include "../../clients/helpers/client_ui_helpers.h"
#include "../view_model/transactions_view_model.h"
#include "../../base/base_screen.h"
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
class clsTransferScreen : protected BaseScreen
{
private:
	static void _PrintClientCard(const BankClientModel& BankClient) {
		std::cout << "Client Card : \n";
		std::cout << "____________________________\n";
		std::cout << "Full Name: " << BankClient.GetFullName() << "\n";
		std::cout << "Acc. Number: " << BankClient.accountNumber << "\n";
		std::cout << "Balance : " << BankClient.accountBalance << "\n";
		std::cout << "____________________________\n\n";
	}
	static ResultStatus _GetBankClientToTransfer(TransactionsViewModel* transactionsViewModel, std::string message, BankClientModel& bankClientModel) {
		std::cout << "\n\n";
		do
		{
			std::string accountNumber = DataReader::ReadAccountNumber(message);
			ResultStatus resultStatusSearchClient = transactionsViewModel->searchClient(bankClientModel,accountNumber);
			if (resultStatusSearchClient == ResultStatus::Found)
			{
				return resultStatusSearchClient;
			}
			else if (resultStatusSearchClient == ResultStatus::NotFound)
			{
				ClientUIHelpers::DisplayResultMessage(resultStatusSearchClient);
				if (DataReader::Confirm("Do you want to try again? (Y/N)? ") != true)
				{
					return ResultStatus::CancelledOperation;
				}
				return resultStatusSearchClient;
			}
			else {
				return resultStatusSearchClient;
			}
		} while (true);
	}
	static ResultStatus _GetTransferClients(BankClientModel& sourceClient, BankClientModel& destinationClient, TransactionsViewModel* transactionsViewModel) {
		ResultStatus sourceClientResultStatus = _GetBankClientToTransfer(transactionsViewModel, "Please Enter Account Number To Transfer From : ", sourceClient);
		if (sourceClientResultStatus == ResultStatus::Found)
		{
			_PrintClientCard(sourceClient);
			ResultStatus destinationClientResultStatus = _GetBankClientToTransfer(transactionsViewModel, "Please Enter Account Number To Transfer To : ", destinationClient);
			if (destinationClientResultStatus == ResultStatus::Found)
			{
				while (destinationClient.accountNumber == sourceClient.accountNumber)
				{
					std::cout << "You are entering the same account number as the transferor. Please enter your receiving account number correctly.\n";
					destinationClientResultStatus = _GetBankClientToTransfer(transactionsViewModel, "Please Enter Account Number To Transfer To : ", destinationClient);
					if (destinationClientResultStatus != ResultStatus::Found)
					{
						return destinationClientResultStatus;
					}
				}
				_PrintClientCard(destinationClient);
				return ResultStatus::Success;
			}
			else
			{
				return destinationClientResultStatus;
			}
		}
		else {
			return sourceClientResultStatus;
		}
	}
	static ResultStatus _ProcessTransfer(BankClientModel& sourceClient, BankClientModel& destinationClient, TransactionsViewModel* transactionsViewModel) {
		float amount = DataReader::PromptAndReadFloatNumberBetween(
			5,
			sourceClient.accountBalance,
			"Please enter amount to transfer : ",
			"Please Enter withdraw amount from 5 EGP to " + std::to_string( sourceClient.accountBalance) + " EGP : "
		);
		cout << "\n\n";
		if (!DataReader::AreYouSure("Are you sure you want to perform this transaction [Y/N] : "))
		{
			return ResultStatus::CancelledOperation;
		}
		cout << "\n\n";
		return transactionsViewModel->transferMoney(sourceClient,destinationClient,amount);
	}
public:
	static void ShowTransfer(TransactionsViewModel* transactionsViewModel) {
		_DrawScreenHeader("\tTransfer Screen");
		std::unique_ptr<BankClientModel> sourceClient = std::make_unique<BankClientModel>();
		std::unique_ptr<BankClientModel> destinationClient = std::make_unique<BankClientModel>();
		ResultStatus resultStatus = _GetTransferClients(*sourceClient, *destinationClient, transactionsViewModel);
		if (resultStatus == ResultStatus::Success)
		{
			ResultStatus TransferResultStatus = _ProcessTransfer(*sourceClient, *destinationClient, transactionsViewModel);
			if (TransferResultStatus == ResultStatus::Success) {
				std::cout << "\nTransfer done Successfully\n";
				_PrintClientCard(*sourceClient);
				std::cout << "\n";
				_PrintClientCard(*destinationClient);
				std::cout << "\n";
			}
			else {
				ClientUIHelpers::DisplayResultMessage(TransferResultStatus);
			}
		}
		else {
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};