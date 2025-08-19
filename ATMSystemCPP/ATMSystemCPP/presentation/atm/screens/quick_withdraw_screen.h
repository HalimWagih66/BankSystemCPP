#pragma once
class QuickWithdrawScreen : BaseScreen
{
private:
	// Displays quick withdrawal options in two columns
	void static ShowWithdrawOptions(const vector<short>& WithdrawOptions) {
		for (size_t i = 0; i < WithdrawOptions.size(); i += 2)
		{
			cout << "\n" << left << setw(19) << "[" + to_string(i + 1) + "] " + to_string(WithdrawOptions[i]);
			if (i + 1 < WithdrawOptions.size())
				cout << "[" + to_string(i + 2) + "] " + to_string(WithdrawOptions[i + 1]) << "\n";
		}
		cout << "\n[" << WithdrawOptions.size() + 1 << "] Exit\n\n";
		cout << "===================================================\n";
	}
	short static ReadQuickWithdrawOption(vector<short> WithdrawOptions) {
		short choice;
		bool IsAmountGreater = false;
		do {
			IsAmountGreater = false;
			choice = DataReader::PromptAndReadShortNumber("Choose What to Withdraw from [1 ~ 9] : "); // Prompt user for a choice
			if (choice <= WithdrawOptions.size())
			{
				if (WithdrawOptions[choice] > CurrentSession::clientLogged->accountBalance)
				{
					cout << "The selected amount is greater than your balance " << CurrentSession::clientLogged->accountBalance << endl;
					IsAmountGreater = true;
					continue;
				}
			}
		} while (choice < 1 || choice > (WithdrawOptions.size() + 1) || IsAmountGreater);
		return choice;
	}
	short static getQuickWithDrawAmount(const short& QuickWithDrawOption)
	{
		switch (QuickWithDrawOption)
		{
		case 1:
			return 20;
		case 2:
			return 50;
		case 3:
			return 100;
		case 4:
			return 200;
		case 5:
			return 400;
		case 6:
			return 600;
		case 7:
			return 800;
		case 8:
			return 1000;
		default:
			return 0;
		}
	}
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
public:
	static void ShowQuickWithdraw(ATMViewModel *atmViewModel) {
		_DrawScreenHeader("Quick Withdraw");

		vector<short> WithdrawOptions = { 20, 50, 100, 200, 400, 600, 800, 1000 };

		ShowWithdrawOptions(WithdrawOptions); // Display the withdrawal options

		cout << "Your Balance is : " << CurrentSession::clientLogged->accountBalance << "\n\n\n";

		short quickWithdrawOption = ReadQuickWithdrawOption(WithdrawOptions); // Read a valid choice from the user
		cout << "\n\n";
		if (quickWithdrawOption == 9) return;

		ProcessWithdrawalIfPossible(getQuickWithDrawAmount(quickWithdrawOption),atmViewModel);
	}
};

