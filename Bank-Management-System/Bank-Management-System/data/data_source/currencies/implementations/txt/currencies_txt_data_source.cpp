#pragma once
#include "currencies_txt_data_source.h" 
#include "../../../../../core/constants/file_pathes/file_pathes.h"
#include "../../../../services/txt/file_txt_manager.h"
#include "../../../../../core/utils/headers/string_utils.h"
#include <vector>
#include <memory>
#include "../../../../models/currency_model.h"
#include <string>
using namespace std;

// Constructor (private in singleton pattern)
CurrenciesTxtDataSource::CurrenciesTxtDataSource() {
}

// Initialize the singleton instance
unique_ptr<CurrenciesTxtDataSource> CurrenciesTxtDataSource::_instance = nullptr;

// Convert a line from the file into a CurrencyModel object
CurrencyModel CurrenciesTxtDataSource::_ConvertLinetoCurrencyObject(string Line, string Seperator)
{
    vector<string> vCurrencyData = StringUtils::SplitString(Line, Seperator);
    return CurrencyModel(vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
}

// Convert a CurrencyModel object into a string to save in the file
string CurrenciesTxtDataSource::_ConverCurrencyObjectToLine(CurrencyModel currency, string Seperator)
{
    string stCurrencyRecord = "";
    stCurrencyRecord += currency.Country + Seperator;
    stCurrencyRecord += currency.CurrencyCode + Seperator;
    stCurrencyRecord += currency.CurrencyName + Seperator;
    stCurrencyRecord += to_string(currency.Rate);
    return stCurrencyRecord;
}

// Save all currencies to the text file
ResultStatus CurrenciesTxtDataSource::saveAllCurrencies(std::vector<CurrencyModel>& outCurrencies) {
    try {
        unique_ptr<vector<string>> contentCurrencies = make_unique<vector<string>>();
        for (const CurrencyModel& currency : outCurrencies) {
            contentCurrencies->push_back(_ConverCurrencyObjectToLine(currency));
        }

        FileTxtManager::SaveLinesInFile(*contentCurrencies, FilePathes::Currencies);
        return ResultStatus::Success;
    }
    catch (const std::exception&) {
        return ResultStatus::Failed;
    }
}

// Update an existing currency by matching CurrencyCode
ResultStatus CurrenciesTxtDataSource::updateCurrency(CurrencyModel& currency) {
    std::unique_ptr<std::vector<CurrencyModel>> currencies = std::make_unique<std::vector<CurrencyModel>>();
    ResultStatus resultStatus = getAllCurrencies(*currencies);

    if (resultStatus != ResultStatus::Success) {
        return resultStatus;
    }

    for (CurrencyModel& c : *currencies) {
        if (c.CurrencyCode == currency.CurrencyCode) {
            c = currency;
            return saveAllCurrencies(*currencies);
        }
    }

    return ResultStatus::NotFound;
}

// Retrieve all currencies from the file
ResultStatus CurrenciesTxtDataSource::getAllCurrencies(std::vector<CurrencyModel>& outCurrencies) {
    try {
        unique_ptr<vector<string>> contentCurrencies = FileTxtManager::GetLinesFromFile(FilePathes::Currencies);
        if (contentCurrencies == nullptr) {
            return ResultStatus::Failed;
        }

        for (const string& line : *contentCurrencies) {
            outCurrencies.push_back(_ConvertLinetoCurrencyObject(line));
        }

        return ResultStatus::Success;
    }
    catch (const std::exception&) {
        return ResultStatus::Failed;
    }
}

// Find a currency by its currency code
ResultStatus CurrenciesTxtDataSource::findByCode(CurrencyModel& currency, const string& currencyCode) {
    std::unique_ptr<std::vector<CurrencyModel>> currencies = std::make_unique<std::vector<CurrencyModel>>();
    ResultStatus resultStatus = getAllCurrencies(*currencies);

    if (resultStatus != ResultStatus::Success) {
        return resultStatus;
    }

    for (const CurrencyModel& c : *currencies) {
        if (StringUtils::ToUpperCase(c.CurrencyCode) == StringUtils::ToUpperCase(currencyCode)) {
            currency = c;
            return ResultStatus::Found;
        }
    }

    return ResultStatus::NotFound;
}

// Find a currency by its country name
ResultStatus CurrenciesTxtDataSource::findByCountry(CurrencyModel& currency, const string& country) {
    std::unique_ptr<std::vector<CurrencyModel>> currencies = std::make_unique<std::vector<CurrencyModel>>();
    ResultStatus resultStatus = getAllCurrencies(*currencies);

    if (resultStatus != ResultStatus::Success) {
        return resultStatus;
    }

    for (const CurrencyModel& c : *currencies) {
        if (StringUtils::ToUpperCase(c.Country) == StringUtils::ToUpperCase(country)) {
            currency = c;
            return ResultStatus::Found;
        }
    }

    return ResultStatus::NotFound;
}

// Singleton getter method
CurrenciesTxtDataSource* CurrenciesTxtDataSource::getInstance() {
    if (_instance == nullptr) {
        _instance = std::unique_ptr<CurrenciesTxtDataSource>(new CurrenciesTxtDataSource());
    }
    return _instance.get();
}
