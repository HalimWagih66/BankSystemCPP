#pragma once
#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../../base/base_screen.h"
#include "../helpers/client_ui_helpers.h"
#include "../view_model/clients_view_model.h"
using namespace std;
class clsUpdateClientScreen : public BaseScreen
{
	static void _ReadClientUpdateInfo(BankClientModel& bankClientModel) {
		if (DataReader::AreYouSure("\nAre You Want Edit First Name? (Y/N): "))
			bankClientModel.FirstName = DataReader::ReadValidName("First");

		if (DataReader::AreYouSure("\nAre You Want Edit Last Name? (Y/N): "))
			bankClientModel.LastName = DataReader::ReadValidName("Last");

		if (DataReader::AreYouSure("\Are You Want Edit Email? (Y/N): "))
			bankClientModel.Email = DataReader::ReadValidEmail();

		if (DataReader::AreYouSure("\nAre You Want Edit Phone Number? (Y/N): "))
			bankClientModel.PhoneNumber = DataReader::ReadValidPhoneNumber();

		if (DataReader::AreYouSure("\nAre You Want Edit Pin Code? (Y/N): "))
			bankClientModel.PinCode = DataReader::ReadValidPinCode();

		cout << "\n______________________________\n";
	}
	static void _DisplayAndUpdateClient(BankClientModel &bankClientModel, ClientsViewModel* clientDataSource) {
		bankClientModel.PrintInfo();
		if (DataReader::AreYouSure("\nAre you sure you want to update this client's information? (Y/N): "))
		{
			cout << "Please enter the new information below: \n";
			_ReadClientUpdateInfo(bankClientModel);
			if (clientDataSource->updateClient(bankClientModel) == ResultStatus::Success) {
				cout << "\n Client updated successfully.\n";
				cout << "\n Client info after update:\n";
				bankClientModel.PrintInfo();
			}
			else
			{
				cout << "\n Error: Could not update client.\n";
			}
		}
		else
		{
			cout << "\n Update cancelled by user.\n";
		}

	}
public:
	static void ShowUpdateClient(ClientsViewModel* clientsViewModel) {
		if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pUpdateClients)) return;


		_DrawScreenHeader("\tUpdate Client Screen");

		cout << "Please Enter the Account Number of the Client to Update: \n\n";

		string AccountNumber = DataReader::ReadAccountNumber();

		unique_ptr<BankClientModel> bankClientModel = std::make_unique<BankClientModel>();

		ResultStatus resultStatus = clientsViewModel->searchClient(*bankClientModel, AccountNumber);

		if (resultStatus == ResultStatus::Found)
		{
			_DisplayAndUpdateClient(*bankClientModel, clientsViewModel);
		}
		else {
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};