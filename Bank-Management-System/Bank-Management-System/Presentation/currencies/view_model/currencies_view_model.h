#pragma once

#include "../../../data/data_source/currencies/interface/interface_currencies_data_source.h"
#include <memory>
#include <vector>
#include "../../../data/models/currency_model.h"

// ViewModel responsible for managing currency data and conversions
class CurrenciesViewModel
{
private:
    // Pointer to the data source for currency operations (e.g., loading, updating)
    ICurrenciesDataSource* _currenciesDataSource;

    // Private constructor to enforce singleton pattern
    CurrenciesViewModel(ICurrenciesDataSource* currenciesTxtDataSource);

    // Singleton instance of the ViewModel
    static std::unique_ptr<CurrenciesViewModel> _instance;

public:
    // Returns the singleton instance, creating it with the provided data source if necessary
    static CurrenciesViewModel* getInstance(ICurrenciesDataSource* currenciesTxtDataSource);

    // Retrieves all currencies from the data source and fills the provided vector
    ResultStatus getAllCurrencies(std::vector<CurrencyModel>& currencies);

    // Finds a currency by its currency code (e.g., "USD", "EUR")
    ResultStatus findByCurrencyCode(CurrencyModel& currency, const std::string& currencyCode);

    // Finds a currency by the country name (e.g., "Germany", "Egypt")
    ResultStatus findByCountry(CurrencyModel& currency, const std::string& country);

    // Updates an existing currency's data (e.g., exchange rate)
    ResultStatus updateCurrency(CurrencyModel& currency);

    // Converts an amount in USD to the target currency
    double convertUSDTo(CurrencyModel& currency, const float& amount);

    // Converts an amount from the target currency to USD
    double convertToUSD(CurrencyModel& currency, const float& amount);

    // Converts an amount from one currency to another
    double convertCurrency(CurrencyModel& currency1, CurrencyModel& currency2, const float& amount);
};
