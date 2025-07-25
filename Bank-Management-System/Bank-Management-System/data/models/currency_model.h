#pragma once
#include <string>

class CurrencyModel {
private:
    std::string _country;
    std::string _currencyCode;
    std::string _currencyName;
    float _rate;

public:
    // Default Constructor
    CurrencyModel()
        : _country(""), _currencyCode(""), _currencyName(""), _rate(0.0f) {
    }

    // Parameterized Constructor
    CurrencyModel(std::string country, std::string currencyCode, std::string currencyName, float rate)
        : _country(country), _currencyCode(currencyCode), _currencyName(currencyName), _rate(rate) {
    }

    // Setters and Getters
    void SetCountry(const std::string& country) { _country = country; }
    std::string GetCountry() const { return _country; }

    void SetCurrencyCode(const std::string& code) { _currencyCode = code; }
    std::string GetCurrencyCode() const { return _currencyCode; }

    void SetCurrencyName(const std::string& name) { _currencyName = name; }
    std::string GetCurrencyName() const { return _currencyName; }

    void SetRate(float rate) { _rate = rate; }
    float GetRate() const { return _rate; }

    // Properties using __declspec(property)
    __declspec(property(get = GetCountry, put = SetCountry)) std::string Country;
    __declspec(property(get = GetCurrencyCode, put = SetCurrencyCode)) std::string CurrencyCode;
    __declspec(property(get = GetCurrencyName, put = SetCurrencyName)) std::string CurrencyName;
    __declspec(property(get = GetRate, put = SetRate)) float Rate;
};
