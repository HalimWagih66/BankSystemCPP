#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../../../models/currency_model.h"
#include "../../../../core/types/result_status.h"

// This is an abstract interface for accessing and managing currency data.
// Any class that implements this interface must define these methods.
class ICurrenciesDataSource
{
public:
    // Retrieves all currency records and stores them in outCurrencies.
    virtual ResultStatus getAllCurrencies(std::vector<CurrencyModel>& outCurrencies) = 0;

    // Finds a currency by its currency code and returns it in outCurrency.
    virtual ResultStatus findByCode(CurrencyModel& outCurrency, const std::string& currencyCode) = 0;

    // Finds a currency by country name and returns it in outCurrency.
    virtual ResultStatus findByCountry(CurrencyModel& outCurrency, const std::string& Country) = 0;

    // Updates an existing currency record.
    virtual ResultStatus updateCurrency(CurrencyModel& currency) = 0;
};
