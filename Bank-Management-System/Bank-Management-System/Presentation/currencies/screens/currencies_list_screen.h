#pragma once
#include <vector>
#include <memory>
#include "../view_model/currencies_view_model.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "../../../Presentation/base/base_screen.h"
#include "../../../data/models/currency_model.h"
#include "../../currencies/helpers/currency_ui_helpers.h"
class CurrenciesListScreen :protected BaseScreen
{

private:
    static void PrintCurrencyRecordLine(CurrencyModel currency)
    {

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(30) << std::left << currency.Country;
        std::cout << "| " << std::setw(8) << std::left << currency.CurrencyCode;
        std::cout << "| " << std::setw(45) << std::left << currency.CurrencyName;
        std::cout << "| " << std::setw(10) << std::left << currency.Rate;

    }
    static void printLineSeperator() {
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "_______________________________________________\n" << std::endl;
    }
    static void _printTableHeader()
    {
        printLineSeperator();


        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(30) << "Country";
        std::cout << "| " << std::left << std::setw(8) << "Code";
        std::cout << "| " << std::left << std::setw(45) << "Name";
        std::cout << "| " << std::left << std::setw(10) << "Rate/(1$)";
        printLineSeperator();
	}
    static void _printTableBody(const std::vector<CurrencyModel> &vCurrencyies) {
        if (vCurrencyies.size() == 0)
            std::cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (const CurrencyModel& Currency : vCurrencyies)
            {
                PrintCurrencyRecordLine(Currency);
                std::cout << std::endl;
            }

        printLineSeperator();
    }
    static void _printTable(const std::vector<CurrencyModel>& vCurrencyies) {
        _printTableHeader();
        _printTableBody(vCurrencyies);
    }
public:
    static void ShowCurrenciesListScreen(CurrenciesViewModel* currenciesViewModel)
    {

		std::unique_ptr<std::vector<CurrencyModel>> vCurrencies = std::make_unique<std::vector<CurrencyModel>>();
        ResultStatus resultStatus = currenciesViewModel->getAllCurrencies(*vCurrencies);
       if (resultStatus != ResultStatus::Success)
        {
           CurrenciesUIHelpers::DisplayResultMessage(resultStatus);
           return;
	    }
        std::string Title = "\t  Currencies List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vCurrencies->size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);
        
        _printTable(*vCurrencies);

    }

};

