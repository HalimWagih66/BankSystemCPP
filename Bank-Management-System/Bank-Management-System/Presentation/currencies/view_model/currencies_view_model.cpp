#include "currencies_view_model.h"
#include <memory>
#include <string>
#include "../../../core/types/result_status.h"
#include "../../../data/data_source/currencies/interface/interface_currencies_data_source.h"

using namespace std;

// Initialize the singleton instance of CurrenciesViewModel to nullptr
unique_ptr<CurrenciesViewModel> CurrenciesViewModel::_instance = nullptr;

// Private constructor that accepts a currency data source via dependency injection
CurrenciesViewModel::CurrenciesViewModel(ICurrenciesDataSource* currenciesTxtDataSource) {
    this->_currenciesDataSource = currenciesTxtDataSource;
}

// Retrieves all available currencies from the data source
ResultStatus CurrenciesViewModel::getAllCurrencies(std::vector<CurrencyModel>& currencies) {
    return _currenciesDataSource->getAllCurrencies(currencies);
}

// Finds a currency by its currency code (e.g., "USD", "EUR")
ResultStatus CurrenciesViewModel::findByCurrencyCode(CurrencyModel& currency, const string& currencyCode) {
    return _currenciesDataSource->findByCode(currency, currencyCode);
}

// Finds a currency by its country name (e.g., "Egypt", "Germany")
ResultStatus CurrenciesViewModel::findByCountry(CurrencyModel& currency, const string& currencyCode) {
    return _currenciesDataSource->findByCountry(currency, currencyCode);
}

// Updates the exchange rate or info of a specific currency
ResultStatus CurrenciesViewModel::updateCurrency(CurrencyModel& currency) {
    return _currenciesDataSource->updateCurrency(currency);
}

// Converts a USD amount to the specified currency
double CurrenciesViewModel::convertUSDTo(CurrencyModel& currency, const float& amount) {
    return amount * currency.Rate;
}

// Converts a foreign currency amount to USD
double CurrenciesViewModel::convertToUSD(CurrencyModel& currency, const float& amount) {
    return amount / currency.Rate;
}

// Converts from one currency to another using their exchange rates
double CurrenciesViewModel::convertCurrency(CurrencyModel& currency1, CurrencyModel& currency2, const float& amount) {
    return ((amount / currency1.Rate) * currency2.Rate);
}

// Singleton instance getter - creates the instance only once with the provided data source
CurrenciesViewModel* CurrenciesViewModel::getInstance(ICurrenciesDataSource* currenciesTxtDataSource) {
    if (_instance == nullptr)
    {
        _instance = unique_ptr<CurrenciesViewModel>(new CurrenciesViewModel(currenciesTxtDataSource));
    }
    return _instance.get();
}
