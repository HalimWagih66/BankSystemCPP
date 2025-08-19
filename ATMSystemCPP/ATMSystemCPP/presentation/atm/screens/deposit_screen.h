#pragma once
class DepositScreen : BaseScreen
{
private:
	// Reads a valid amount for deposit (must be positive)
	int static ReadAmountForDeposit() {
		int amount = 0;
		do {
			amount = DataReader::PromptAndReadDblNumberBetween(5,80000,"Please enter the amount you want to deposit must be positive : ","Please enter an amount from 5 to 80,000");
			if (amount <= 0) {
				cout << "Invalid amount. Please enter a positive value.\n";
			}
		} while (amount <= 0);
		return amount;
	}
	void static PerformDepositOption(const int& amount,ATMViewModel* atmViewModel)
	{
		if (DataReader::AreYouSure("Are you sure you want to deposit " + to_string(amount) + " ? [Y/N]? ")) {
			atmViewModel->depositAmount(amount);
			cout << "\n\nDeposit successful! New Balance is : " << CurrentSession::clientLogged->accountBalance << endl;
		}
		else {
			cout << "The deposit was not completed. Your balance remains the same.\n"; // If user cancels, show a message
		}
	}
public:
	static void showDeposit(ATMViewModel* atmViewModel) {
		_DrawScreenHeader("Deposit Screen"); // Show the deposit screen header

		int amount = ReadAmountForDeposit(); // Read a valid amount for deposit

		cout << "\n\n";

		PerformDepositOption(amount,atmViewModel); // Perform the deposit operation with the entered amount
	}
};

