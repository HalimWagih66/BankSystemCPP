#pragma once
#include "../../../core/utils/headers/string_utils.h"
#include "../view_model/currencies_view_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include <iostream>
#include "../../base/base_screen.h"
#include "../../../core/types/result_status.h"
#include "../../../data/models/currency_model.h"
class FindCurrencyScreen :protected BaseScreen {
private:
    static void _PrintCurrency(const CurrencyModel& Currency)
    {
        std::cout << "\nCurrency Card:\n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry    : " << Currency.Country;
        std::cout << "\nCode       : " << Currency.CurrencyCode;
        std::cout << "\nName       : " << Currency.CurrencyName;
        std::cout << "\nRate(1$) = : " << Currency.Rate;

        std::cout << "\n_____________________________\n";
    }
    static void _ShowResults(const CurrencyModel& Currency, const ResultStatus resultStatus)
    {
        if (resultStatus == ResultStatus::Found)
        {
            std::cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            std::cout << "\nCurrency Was not Found :-(\n";
        }
    }
public:
    static void ShowFindCurrencyScreen(CurrenciesViewModel* currenciesViewModel) {
        _DrawScreenHeader("\t  Find Currency Screen");

        short answer = DataReader::PromptAndReadShortNumber("\nFind By: [1] Code or [2] Country ? ");

        if (answer != 1 && answer != 2)
        {
            std::cout << "\nInvalid Option Selected, Please Try Again.\n";
            return;
		}
        std::unique_ptr<CurrencyModel> Currency = std::make_unique<CurrencyModel>();
        if (answer == 1)
        {
            std::string CurrencyCode = DataReader::CurrencyCode();
            ResultStatus resultStatus = currenciesViewModel->findByCurrencyCode(*Currency, CurrencyCode);
            _ShowResults(*Currency, resultStatus);
        }
		else if (answer == 2)
        {
            std::string Country = DataReader::PromptAndReadLine("Please Enter Country Name : ");
            ResultStatus resultStatus = currenciesViewModel->findByCountry(*Currency, Country);
            _ShowResults(*Currency, resultStatus);
        }

    }
};