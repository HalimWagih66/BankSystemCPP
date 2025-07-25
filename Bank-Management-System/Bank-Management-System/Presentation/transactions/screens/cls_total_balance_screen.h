#pragma once
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include "../../data/models/bank_client_model.h"
#include "../../core/utils/headers/string_utils.h"
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../../clients/helpers/client_ui_helpers.h"
#include "../view_model/transactions_view_model.h"
#include "../../base/base_screen.h"
class clsTotalBalanceScreen : BaseScreen
{
private:
	static double _CalculateBalances(const std::vector<BankClientModel>& vClients) {
		double total = 0;
		for (const BankClientModel& bankClientModel : vClients)
		{
			total += bankClientModel.accountBalance;
		}
		return total;
	}
	static void _PrintClientRecordBalanceLine(const BankClientModel& Client)
	{

		std::cout << "| " << std::setw(15) << std::left << Client.accountNumber;
		std::cout << "| " << std::setw(40) << std::left << Client.GetFullName();
		std::cout << "| " << std::setw(12) << std::left << std::fixed << std::setprecision(2) << Client.accountBalance;
	}
	static void _DisplayTotalBalancesTable(std::vector<BankClientModel>& vClients) {
		std::cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
		std::cout << "\n_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;

		std::cout << "| " << std::left << std::setw(15) << "Account Number";
		std::cout << "| " << std::left << std::setw(40) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << "\n_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;

		double TotalBalances = _CalculateBalances(vClients);

		if (vClients.size() == 0)
			std::cout << "\t\t\t\tNo Clients Available In the System!";
		else {
			for (const BankClientModel& Client : vClients)
			{
				_PrintClientRecordBalanceLine(Client);
				std::cout << std::endl;
			}

			std::cout << "\n_______________________________________________________";
			std::cout << "_________________________________________\n" << std::endl;
			std::cout << "\t\t\t\t\t   Total Balances = " << std::fixed << std::setprecision(2) << TotalBalances << " EGP\n";
			std::cout << "\t\t\t\t\t   ( " << StringUtils::NumberToText(TotalBalances) << ")";
		}
	}
public:
	static void ShowTotalBalancesScreen(TransactionsViewModel* transactionsViewModel)
	{
		std::unique_ptr<std::vector<BankClientModel>> vClients = std::make_unique<std::vector<BankClientModel>>();
		ResultStatus resultStatus = transactionsViewModel->getClients(*vClients);
		std::string Title = "\tTotal Balances Screen";
		if (resultStatus == ResultStatus::Success)
		{
			std::string SubTitle = "\t   (" + std::to_string(vClients->size()) + ") Client(s)\n";
			_DrawScreenHeader(Title);
			_DisplayTotalBalancesTable(*vClients);
		}
		else
		{
			_DrawScreenHeader(Title);
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
		std::cout << std::endl;
	}
};

