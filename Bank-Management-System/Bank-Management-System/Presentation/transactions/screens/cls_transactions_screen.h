#pragma once
#include <iostream>
#include <iomanip>
#include "../../base/base_screen.h"
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
#include "cls_deposit_screen.h"
#include "cls_withdraw_screen.h"
#include "cls_total_balance_screen.h"
#include "cls_transfer_screen.h"
#include "cls_transfers_log_screen.h"
#include "../../transactions/view_model/transactions_view_model.h"
using namespace std;
class clsTransactionsScreen : BaseScreen
{
	TransactionsViewModel* transactionsViewModel;
private:
	enum enTransactionsMenueOptions
	{
		eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eTransfer = 4, eTransfersLog = 5, eShowMainMenue = 6
	};
	short _ReadTransactionsMenueOption() {
		cout << std::setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = DataReader::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen(transactionsViewModel);
	}
	void _ShowWithdrawScreen() {
		clsWithdrawScreen::ShowWithdrawScreen(transactionsViewModel);
	}
	void _ShowTotalBalancesScreen() {
		clsTotalBalanceScreen::ShowTotalBalancesScreen(transactionsViewModel);
	}
	void _GoBackToTransactionsMenue() {
		cout << std::setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";

		system("pause>0");
		ShowTransactionsMenue();
	}
	void _ShowTransferScreen() {
		clsTransferScreen::ShowTransfer(transactionsViewModel);
	}
	void _ShowTransfersLogScreen() {
		clsTransfersLogScreen::ShowTransfersLog(transactionsViewModel);
	}
	void _PerformTransactionsMenueOption(enTransactionsMenueOptions Option) {
		switch (Option) {
		case eDeposit:
			ConsoleHelper::ClearScreen();
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		case eWithdraw:
			ConsoleHelper::ClearScreen();
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		case eShowTotalBalance:
			ConsoleHelper::ClearScreen();
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		case eTransfer:
			ConsoleHelper::ClearScreen();
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		case eTransfersLog:
			ConsoleHelper::ClearScreen();
			_ShowTransfersLogScreen();
			_GoBackToTransactionsMenue();
			break;
		case eShowMainMenue: {
		}
		}
	}
public:
	clsTransactionsScreen(TransactionsViewModel* transactionsViewModel) {
		this->transactionsViewModel = transactionsViewModel;
	}
	void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pTranactions)) return;
		
		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << std::setw(37) << left << "" << "===========================================\n";
		cout << std::setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << std::setw(37) << left << "" << "===========================================\n";
		cout << std::setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << std::setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << std::setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << std::setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << std::setw(37) << left << "" << "\t[5] Transfers Log.\n";
		cout << std::setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << std::setw(37) << left << "" << "===========================================\n";

		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}
};