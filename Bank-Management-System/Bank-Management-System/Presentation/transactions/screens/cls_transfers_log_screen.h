#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>
#include "../../base/base_screen.h"

#include "../../core/types/result_status.h"
#include "../../clients/helpers/client_ui_helpers.h"
#include "../view_model/transactions_view_model.h"
#include "../../../data/models/transfer_log_model.h"
#include "../../data/data_source/clients/interface/interface_client_data_source.h"
class clsTransfersLogScreen : BaseScreen
{
private:
    static void PrintTransferLogRecordLine(const TransferLogModel& transferLogModel)
    {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(23) << std::left << transferLogModel.dateTime;
        std::cout << "| " << std::setw(16) << std::left << transferLogModel.sourceAccountNumber;
        std::cout << "| " << std::setw(16) << std::left << transferLogModel.destinationAccountNumber;
        std::cout << "| " << std::setw(8) << std::left << transferLogModel.amount;
        std::cout << "| " << std::setw(10) << std::left << transferLogModel.srcBalanceAfter;
        std::cout << "| " << std::setw(10) << std::left << transferLogModel.destBalanceAfter;
        std::cout << "| " << std::setw(8) << std::left << transferLogModel.Username;
    }
    static void Seperator() {
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________________\n" << std::endl;
    }
    static void DisplayTransfersLogHeaderTable() {
        Seperator();

        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(23) << "Date/Time";
        std::cout << "| " << std::left << std::setw(16) << "s.Acct";
        std::cout << "| " << std::left << std::setw(16) << "d.Acct";
        std::cout << "| " << std::left << std::setw(8) << "Amount";
        std::cout << "| " << std::left << std::setw(10) << "s.Balance";
        std::cout << "| " << std::left << std::setw(10) << "d.Balance";
        std::cout << "| " << std::left << std::setw(8) << "User";

        Seperator();
    }
    static void DisplayTransfersLogBodyTable(std::vector<TransferLogModel>& vTransferLogRecord) {
        if (vTransferLogRecord.size() == 0)
            std::cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (const TransferLogModel &Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                std::cout << std::endl;
            }

        Seperator();
    }
    static void DisplayTransfersLogTable(std::vector<TransferLogModel>& vTransferLogRecord) {
        DisplayTransfersLogHeaderTable();
        DisplayTransfersLogBodyTable(vTransferLogRecord);
    }
public:
    static void ShowTransfersLog(TransactionsViewModel* transactionsViewModel) {
        std::unique_ptr<std::vector<TransferLogModel>> vTransferLogRecord = std::make_unique<std::vector<TransferLogModel>>();
        ResultStatus resultStatus = transactionsViewModel->getTransferLogs(*vTransferLogRecord);
        if (resultStatus != ResultStatus::Success)
        {
            _DrawScreenHeader("\tTransfer Log List Screen");
            ClientUIHelpers::DisplayResultMessage(resultStatus);
            return;
        }
        std::string Title = "\tTransfer Log List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vTransferLogRecord->size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        DisplayTransfersLogTable(*vTransferLogRecord);
    }
};