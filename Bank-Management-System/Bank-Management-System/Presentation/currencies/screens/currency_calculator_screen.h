#include <memory>
#include "../helpers/currency_ui_helpers.h"
#include "../view_model/currencies_view_model.h"
#include "../../../core/utils/headers/data_reader.h"
#include <iostream>
#include "../../../core/types/result_status.h"
#include "../../../data/models/currency_model.h"
#include <string>
#include "../../../core/utils/headers/string_utils.h"
#include "../../base/base_screen.h"
class CurrencyCalculatorScreen : protected BaseScreen
{
	static ResultStatus _getCurrency(CurrencyModel& currencyModel, std::string currencyCode,CurrenciesViewModel* currenciesViewModel) {
        ResultStatus resultStatus = currenciesViewModel->findByCurrencyCode(currencyModel,currencyCode);
        if (resultStatus == ResultStatus::Found)return resultStatus;
        while (resultStatus == ResultStatus::NotFound) {
            CurrenciesUIHelpers::DisplayResultMessage(resultStatus);
            if (DataReader::Confirm("Do you want to continue searching Y/N? "))
            {
                currencyCode = DataReader::CurrencyCode();
                resultStatus = currenciesViewModel->findByCurrencyCode(currencyModel, currencyCode);
            }
            else
            {
                return ResultStatus::CancelledOperation;
            }
        }
        return resultStatus;
	}
	static ResultStatus _getCurrencies(CurrencyModel& currency1, CurrencyModel& currency2, CurrenciesViewModel* currenciesViewModel) {
        std::string currencyCode = DataReader::CurrencyCode("Please Enter currency1 Code: ");
        ResultStatus resultStatusGetCurrency = _getCurrency(currency1,currencyCode, currenciesViewModel);
        if (resultStatusGetCurrency != ResultStatus::Found)
        {
            return resultStatusGetCurrency;
        }
        currencyCode = DataReader::CurrencyCode("Please Enter currency2 Code: ");
        while (currencyCode == currency1.CurrencyCode) {
            std::cout << "\nyou are reusing the same currency code and this wrong please enter different currency code\n";
            currencyCode = DataReader::CurrencyCode("\nPlease Enter currency2 Code : ");
        }
  
        resultStatusGetCurrency = _getCurrency(currency2,currencyCode, currenciesViewModel);
        if (resultStatusGetCurrency == ResultStatus::Found)
        {
            return ResultStatus::Success;
        }
        else
        {
            return resultStatusGetCurrency;
        }
	}
    static void _PrintCurrency(const CurrencyModel& Currency,const std::string title)
    {
        std::cout << "\n"<<title<<" : \n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry    : " << Currency.Country;
        std::cout << "\nCode       : " << Currency.CurrencyCode;
        std::cout << "\nName       : " << Currency.CurrencyName;
        std::cout << "\nRate(1$) = : " << Currency.Rate;
        std::cout << "\n_____________________________\n";
    }
    static void calculatorProcess(CurrencyModel& currency1, CurrencyModel& currency2, CurrenciesViewModel* currenciesViewModel) {
        float amountExchange = DataReader::PromptAndReadFloatNumberBetween(1,100000,"Please Enter Amount to Excange: ", "Please Enter Amount from 0 to 100000 to Excange: ");
        if (currency1.CurrencyCode == "USD")
        {
            _PrintCurrency(currency2,"Convert To");
            std::cout << "\n";
            std::cout << amountExchange << " " << currency1.CurrencyCode << " = " << currenciesViewModel->convertUSDTo(currency2, amountExchange) << " " << currency2.CurrencyCode << std::endl;
        }
        else if(currency2.CurrencyCode == "USD")
        {
            _PrintCurrency(currency1,"Convert From");
            std::cout << "\n";
            std::cout << amountExchange << " " << currency1.CurrencyCode << " = " << currenciesViewModel->convertToUSD(currency1, amountExchange) << " " << currency2.CurrencyCode << std::endl;
        }
        else
        {
            _PrintCurrency(currency1, "Convert From");
            std::cout << "\n";
            std::cout << amountExchange << " " << currency1.CurrencyCode << " = " << currenciesViewModel->convertToUSD(currency1, amountExchange) << " USD" << std::endl;
            std::cout << "\n";
            _PrintCurrency(currency2, "Convert To");
            std::cout << "\n";
            std::cout << amountExchange << " " << currency1.CurrencyCode << " = " << currenciesViewModel->convertCurrency(currency1,currency2, amountExchange) << " " << currency2.CurrencyCode << std::endl;
        }
    }
public:
    static void showCurrencyCalculator(CurrenciesViewModel* currenciesViewModel) {
        _DrawScreenHeader("\tCurrency Calculator Screen");
        std::unique_ptr<CurrencyModel> currency1 = std::make_unique<CurrencyModel>();
        std::unique_ptr<CurrencyModel> currency2 = std::make_unique<CurrencyModel>();
        do
        {
            ConsoleHelper::ClearScreen();
            _DrawScreenHeader("\tCurrency Calculator Screen");
            ResultStatus resultStatus = _getCurrencies(*currency1, *currency2, currenciesViewModel);
            if (resultStatus == ResultStatus::Success)
            {
                calculatorProcess(*currency1, *currency2, currenciesViewModel);
            }
            else {
                CurrenciesUIHelpers::DisplayResultMessage(resultStatus);
                return;
            }
        } while (DataReader::Confirm("Do you want to perform another calculation? Y/N? "));
        
    }
};