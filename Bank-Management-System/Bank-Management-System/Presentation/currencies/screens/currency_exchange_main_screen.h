#pragma once
#include "../../../di/view_model_provider/view_model_provider.h"
#include "../view_model/currencies_view_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include <iostream>
#include <iomanip>
#include "../../../Presentation/currencies/screens/find_currency_screen.h"
#include "../../base/base_screen.h"
#include "../../../Presentation/currencies/screens/update_currency_rate_screen.h"
#include "currencies_list_screen.h"
#include "currency_calculator_screen.h"
class clsCurrencyExchangeMainScreen :protected BaseScreen
{
    CurrenciesViewModel* _currenciesViewModel;
private:
    enum enCurrenciesMainMenueOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4, eMainMenue = 5
    };

    static short ReadCurrenciesMainMenueOptions()
    {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = DataReader::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrenciesMenue()
    {
        std::cout << "\n\nPress any key to go back to Currencies Menue...";
        system("pause>0");
        ShowCurrenciesMenue();
    }

    static void _ShowCurrenciesListScreen()
    {
        CurrenciesListScreen::ShowCurrenciesListScreen(ViewModelProvider::getCurrenciesViewModel());
    }

    static void _ShowFindCurrencyScreen()
    {
        FindCurrencyScreen::ShowFindCurrencyScreen(ViewModelProvider::getCurrenciesViewModel());
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        UpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen(ViewModelProvider::getCurrenciesViewModel());
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        CurrencyCalculatorScreen::showCurrencyCalculator(ViewModelProvider::getCurrenciesViewModel());
    }

    static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions)
    {

        switch (CurrenciesMainMenueOptions)
        {
        case enCurrenciesMainMenueOptions::eListCurrencies:
        {
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eUpdateCurrencyRate:
        {
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }

    }

public:
    clsCurrencyExchangeMainScreen(CurrenciesViewModel* currenciesViewModel) {
        _currenciesViewModel = currenciesViewModel;
    }
    static void ShowCurrenciesMenue()
    {

        system("cls");
        _DrawScreenHeader("    Currancy Exhange Main Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t\t  Currency Exhange Menue\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] List Currencies.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Find Currency.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Update Rate.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Currency Calculator.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Main Menue.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";

        _PerformCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions)ReadCurrenciesMainMenueOptions());
    }

};

