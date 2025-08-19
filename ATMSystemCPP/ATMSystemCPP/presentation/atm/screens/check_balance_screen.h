#pragma once
#include <iostream>
class CheckBalanceScreen : BaseScreen
{
public:
	static void showCheckBalance() {
		_DrawScreenHeader("Check Balance");
		std::cout << "Your Balance is : " << CurrentSession::clientLogged->accountBalance << std::endl;
	}
};

