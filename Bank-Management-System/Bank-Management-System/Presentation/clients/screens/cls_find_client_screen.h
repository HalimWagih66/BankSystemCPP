#pragma once
#include "../../base/base_screen.h"
#include <iostream>
#include <memory>
#include "../../../data/models/bank_client_model.h"
#include "../../../core/types/result_status.h"
#include "../helpers/client_ui_helpers.h"
#include "../../../di/view_model_provider/view_model_provider.h"
class clsFindClientScreen : protected BaseScreen
{
public:
	static void ShowFindClientScreen(ClientsViewModel* clientsViewModel) {
		if (!CheckAccessRights(CurrentSession::UserLogged->enPermissions::pFindClient)) return;


		_DrawScreenHeader("\tFind Client Screen");

		std::cout << "Please Enter the Account Number of the Client to Find: \n\n";

		std::string accountNumber = DataReader::ReadAccountNumber();

		std::unique_ptr<BankClientModel> bankClientModel = std::make_unique<BankClientModel>();

		ResultStatus resultStatus = clientsViewModel->searchClient(*bankClientModel, accountNumber);

		if (resultStatus == ResultStatus::Found)
		{
			bankClientModel->PrintInfo();
		}
		else {
			ClientUIHelpers::DisplayResultMessage(resultStatus);
		}
	}
};