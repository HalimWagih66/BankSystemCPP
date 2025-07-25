#pragma once
#include <string>

class TransferLogModel
{
private:
    std::string _DateTime;
    std::string _SourceAccountNumber;
    std::string _DestinationAccountNumber;
    float _Amount;
    float _SrcBalanceAfter;
    float _DestBalanceAfter;
    std::string _Username;

public:
    // Setters
    void SetDateTime(const std::string& dateTime) { _DateTime = dateTime; }
    void SetSourceAccountNumber(const std::string& acc) { _SourceAccountNumber = acc; }
    void SetDestinationAccountNumber(const std::string& acc) { _DestinationAccountNumber = acc; }
    void SetAmount(float amount) { _Amount = amount; }
    void SetSrcBalanceAfter(float balance) { _SrcBalanceAfter = balance; }
    void SetDestBalanceAfter(float balance) { _DestBalanceAfter = balance; }
    void SetUsername(const std::string& username) { _Username = username; }

    // Getters
    std::string GetDateTime() const { return _DateTime; }
    std::string GetSourceAccountNumber() const { return _SourceAccountNumber; }
    std::string GetDestinationAccountNumber() const { return _DestinationAccountNumber; }
    float GetAmount() const { return _Amount; }
    float GetSrcBalanceAfter() const { return _SrcBalanceAfter; }
    float GetDestBalanceAfter() const { return _DestBalanceAfter; }
    std::string GetUsername() const { return _Username; }

    // Properties using __declspec
    __declspec(property(get = GetDateTime, put = SetDateTime)) std::string dateTime;
    __declspec(property(get = GetSourceAccountNumber, put = SetSourceAccountNumber)) std::string sourceAccountNumber;
    __declspec(property(get = GetDestinationAccountNumber, put = SetDestinationAccountNumber)) std::string destinationAccountNumber;
    __declspec(property(get = GetAmount, put = SetAmount)) float amount;
    __declspec(property(get = GetSrcBalanceAfter, put = SetSrcBalanceAfter)) float srcBalanceAfter;
    __declspec(property(get = GetDestBalanceAfter, put = SetDestBalanceAfter)) float destBalanceAfter;
    __declspec(property(get = GetUsername, put = SetUsername)) std::string Username;
};
