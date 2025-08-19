#include "../../../data/models/bank_client_model.h"
#include "../../../data/data_source/clients/interface/interface_client_data_source.h"
#include <memory>
#include "../../../core/types/result_status.h"
class ATMViewModel
{
	static std::unique_ptr<ATMViewModel> _instance;

	IClientDataSource* _dataSource;

	ATMViewModel(IClientDataSource* dataSource);
public:
	ResultStatus withdrawAmount(int amount);

	ResultStatus depositAmount(int amount);

	ResultStatus transferAmount(int amount, BankClientModel& sourceClient, BankClientModel& destinationClient);

	static ATMViewModel* getInstance(IClientDataSource* dataSource);
};
