#pragma once
#include "../../base/base_screen.h"
#include <iostream>
class NormalWithdrawScreen : BaseScreen
{
private:
	// Performs withdrawal if balance is sufficient
	static void ProcessWithdrawalIfPossible(const int& amount, ATMViewModel* atmViewModel)
	{
		if (DataReader::AreYouSure("Are you sure you want perform this transaction? [Y/N]? ")) {
			atmViewModel->withdrawAmount(amount);
			std::cout << "\n\nDone Successfully. New Balance is : " << CurrentSession::clientLogged->accountBalance << std::endl;
		}
		else {
			std::cout << "The transaction was not completed. Your balance remains the same.\n";
		}
	}
	static int ReadAmountToWithdraw() {
		int amount;
		do
		{
			amount = DataReader::ReadAmountMultipleOfFive();
			if (amount > CurrentSession::clientLogged->accountBalance)
				std::cout << "\nPlease enter amount from 5 EG Pound to " + std::to_string(CurrentSession::clientLogged->accountBalance) << " EG Pound\n";
			else
				return amount;
		} while (true);
	}
public:
	static void ShowNormalWithdrawScreen(ATMViewModel* atmViewModel) {
		_DrawScreenHeader("Normal Withdraw Screen"); // Draw the screen header
		std::cout << "\n";
		int amount = ReadAmountToWithdraw();
		std::cout << "\n\n";
		ProcessWithdrawalIfPossible(amount, atmViewModel); // Process the withdrawal if possible
	}

};

