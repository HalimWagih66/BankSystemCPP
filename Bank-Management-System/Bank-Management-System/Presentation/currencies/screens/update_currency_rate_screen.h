#pragma once
#include <memory>
#include "../view_model/currencies_view_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include <iostream>
#include <string>
#include "../../base/base_screen.h"
#include "../helpers/currency_ui_helpers.h"
#include "../../../data/models/currency_model.h"
class UpdateCurrencyRateScreen : protected BaseScreen

{
private:
    static void _PrintCurrency(CurrencyModel Currency)
    {
        std::cout << "\nCurrency Card:\n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry    : " << Currency.Country;
        std::cout << "\nCode       : " << Currency.CurrencyCode;
        std::cout << "\nName       : " << Currency.CurrencyName;
        std::cout << "\nRate(1$) = : " << Currency.Rate;
        std::cout << "\n_____________________________\n";
    }
    static void _updateProcess(CurrencyModel& Currency,CurrenciesViewModel* currenciesViewModel) {
        std::cout << "\n\nUpdate Currency Rate:";
        std::cout << "\n____________________\n";
        float newCurrencyRate = DataReader::CurrencyRate();
        Currency.Rate = newCurrencyRate;
        ResultStatus resultStatus = currenciesViewModel->updateCurrency(Currency);
        CurrenciesUIHelpers::DisplayResultMessage(resultStatus,"The currency rate has been updated successfully.");
    }
public:

    static void ShowUpdateCurrencyRateScreen(CurrenciesViewModel *currenciesViewModel)
    {

        _DrawScreenHeader("\tUpdate Currency Screen");


        std::string currencyCode = DataReader::CurrencyCode();

        std::unique_ptr<CurrencyModel> currency = std::make_unique<CurrencyModel>();
        ResultStatus resultStatusFind = currenciesViewModel->findByCurrencyCode(*currency,currencyCode);
        while (resultStatusFind == ResultStatus::NotFound)
        {
            CurrenciesUIHelpers::DisplayResultMessage(resultStatusFind);
            if (!DataReader::Confirm("Are you want continue search Y/N ? "))
            {
                CurrenciesUIHelpers::DisplayResultMessage(ResultStatus::CancelledOperation);
                return;
            }
            std::string currencyCode = DataReader::CurrencyCode();
            ResultStatus resultStatusFind = currenciesViewModel->findByCurrencyCode(*currency, currencyCode);
        }

        _PrintCurrency(*currency);

        _updateProcess(*currency,currenciesViewModel);

    }
};

