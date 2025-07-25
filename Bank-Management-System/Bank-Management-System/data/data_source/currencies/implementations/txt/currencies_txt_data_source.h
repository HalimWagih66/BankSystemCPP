#pragma once

#include "../../../../data_source/currencies/interface/interface_currencies_data_source.h"
#include <memory>
#include <string>
#include <vector>
#include "../../../../models/currency_model.h"

// This class is responsible for managing currency data stored in a text file.
// It implements the ICurrenciesDataSource interface to allow file-based access to currencies.
class CurrenciesTxtDataSource : public ICurrenciesDataSource
{
private:
    // Singleton instance of the class
    static std::unique_ptr<CurrenciesTxtDataSource> _instance;

    // Converts a line of text into a CurrencyModel object
    CurrencyModel _ConvertLinetoCurrencyObject(std::string Line, std::string Seperator = "#//#");

    // Converts a CurrencyModel object into a line of text
    std::string _ConverCurrencyObjectToLine(CurrencyModel currency, std::string Seperator = "#//#");

    // Private constructor for singleton pattern
    CurrenciesTxtDataSource();

public:
    // Updates an existing currency based on its CurrencyCode
    ResultStatus updateCurrency(CurrencyModel& currency);

    // Searches for a currency by country name
    ResultStatus findByCountry(CurrencyModel& outCurrency, const std::string& Country);

    // Retrieves all currencies from the file
    ResultStatus getAllCurrencies(std::vector<CurrencyModel>& outCurrencies);

    // Saves all currencies to the file
    ResultStatus saveAllCurrencies(std::vector<CurrencyModel>& outCurrencies);

    // Searches for a currency by its currency code
    ResultStatus findByCode(CurrencyModel& currency, const std::string& currencyCode);

    // Returns the singleton instance of the data source
    static CurrenciesTxtDataSource* getInstance();
};
