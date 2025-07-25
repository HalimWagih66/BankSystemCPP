#pragma once
#include "../../base/base_screen.h"
#include <iomanip>
#include <vector>
#include <memory>
#include "../../../core/../data/models/bank_client_model.h"
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
#include "../view_model/clients_view_model.h"
#include "../helpers/client_ui_helpers.h"
class clsClientListScreen : protected BaseScreen
{
private:
	static void PrintClientRecordLine(BankClientModel Client)
	{

		std::cout << std::setw(8) << std::left << "" << "| " << std::setw(15) << std::left << Client.accountNumber;
		std::cout << "| " << std::setw(20) << std::left << Client.GetFullName();
		std::cout << "| " << std::setw(12) << std::left << Client.PhoneNumber;
		std::cout << "| " << std::setw(20) << std::left << Client.Email;
		std::cout << "| " << std::setw(10) << std::left << Client.PinCode;
		std::cout << "| " << std::setw(12) << std::left << Client.accountBalance;

	}
	static void PrintHeaderTable() {
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;

		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << "Accout Number";
		std::cout << "| " << std::left << std::setw(20) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(20) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Pin Code";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
	}
	static void PrintTableHeader() {
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;

		std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << "Accout Number";
		std::cout << "| " << std::left << std::setw(20) << "Client Name";
		std::cout << "| " << std::left << std::setw(12) << "Phone";
		std::cout << "| " << std::left << std::setw(20) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Pin Code";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
	}
	static void printBodyHeader(std::vector<BankClientModel>& vClients) {
		if (vClients.size() == 0)
			std::cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (const BankClientModel& Client : vClients)
			{

				PrintClientRecordLine(Client);
				std::cout << std::endl;
			}

		std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
		std::cout << "_________________________________________\n" << std::endl;
	}
	static void printTable(std::vector<BankClientModel>& vClients) {
		PrintTableHeader();
		printBodyHeader(vClients);
	}
public:
	static void ShowClientsList(ClientsViewModel* clientsViewModel) {
		if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pListClients)) return;


		std::unique_ptr<std::vector<BankClientModel>> vClients = std::make_unique<std::vector<BankClientModel>>();;
		ResultStatus resultStatus = clientsViewModel->getAllClients(*vClients);
		if (resultStatus != ResultStatus::Success)
		{
			_DrawScreenHeader("\t  Client List Screen");
			ClientUIHelpers::DisplayResultMessage(resultStatus);
			return;
		}
		std::string Title = "\t  Client List Screen";
		std::string SubTitle = "\t  (" + std::to_string(vClients->size()) + ") Client(s).\n";
		_DrawScreenHeader(Title, SubTitle);

		printTable(*vClients);
	}
};