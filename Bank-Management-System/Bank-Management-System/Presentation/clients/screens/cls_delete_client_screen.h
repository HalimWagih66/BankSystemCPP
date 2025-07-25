#pragma once
#include "../../base/base_screen.h"
#include <iostream>
#include <string>
#include <memory>
#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../helpers/client_ui_helpers.h"
#include "../../../data/models/bank_client_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include "../view_model/clients_view_model.h"
class clsDeleteClientScreen : public BaseScreen
{
	static void DisplayAndDeleteClient(BankClientModel& bankClientModel, ClientsViewModel* clientsViewModel) {
		bankClientModel.PrintInfo();
		if (DataReader::AreYouSure("\nAre you sure you want to delete this client Y/N? "))
		{
			if (clientsViewModel->deleteClient(bankClientModel.accountNumber) == ResultStatus::Success) {
				std::cout << "\nClient deleted successfully." << std::endl;
			}
			else
			{
				std::cout << "\nError: Could not delete client." << std::endl;
			}
		}
		else
		{
			std::cout << "\nClient deletion cancelled\n";
		}
	}
public:
	static void ShowDeleteClientScreen(ClientsViewModel* clientsViewModel) {
		if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pDeleteClient)) return;

		_DrawScreenHeader("\tDelete Client Screen");

		std::cout << "Please Enter the Account Number of the Client to Delete: \n";

		std::string accountNumber = DataReader::ReadAccountNumber();

		std::unique_ptr<BankClientModel> bankClientModel = std::make_unique<BankClientModel>();

		ResultStatus resultStatus = clientsViewModel->searchClient(*bankClientModel, accountNumber);

		if (resultStatus == ResultStatus::Found)
		{
			DisplayAndDeleteClient(*bankClientModel, clientsViewModel);
		}
		else {
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};