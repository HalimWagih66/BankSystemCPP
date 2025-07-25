#pragma once
#include "../../../Presentation/clients/view_model/clients_view_model.h"
#include "../../../data/models/bank_client_model.h"
#include "../../../core/types/result_status.h"
#include <memory>
#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../helpers/client_ui_helpers.h"
#include "../../base/base_screen.h"
using namespace std;
class clsAddNewClientScreen : public BaseScreen
{
private:
	static void _printInfo(const BankClientModel& bankClientModel)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << bankClientModel.FirstName << "\n";
		cout << "\nLastName    : " << bankClientModel.LastName << "\n";
		cout << "\nFull Name   : " << bankClientModel.GetFullName() << "\n";
		cout << "\nEmail       : " << bankClientModel.Email << "\n";
		cout << "\nPhone       : " << bankClientModel.PhoneNumber << "\n";
		cout << "\nAcc. Number : " << bankClientModel.accountNumber << "\n";
		cout << "\nPassword    : " << bankClientModel.PinCode << "\n";
		cout << "\nBalance     : " << bankClientModel.accountBalance << "\n";
		cout << "\n___________________\n";

	}
public:
	static void ShowAddNewClientScreen(ClientsViewModel* clientsViewModel)
	{
		_DrawScreenHeader("\t  Add New Client Screen");

		unique_ptr<BankClientModel>bankClientModel = make_unique<BankClientModel>();

		_printInfo(*bankClientModel);

		try {
			ResultStatus resultStatus = clientsViewModel->addNewClient(*bankClientModel);

			if (resultStatus == ResultStatus::Success)
			{
				ClientUIHelpers::DisplayResultMessage(resultStatus, "\nThe client has been added successfully.\n");

				bankClientModel->PrintInfo();
			}
			else
			{
				ClientUIHelpers::DisplayResultMessage(resultStatus);
			}
		}
		catch (const std::exception& e) {
			cout << "\nFailed to add client: " << e.what() << "\n";
		}
	}
};