#pragma once
#include <string>

class LoginRegisterModel
{
private:
    std::string _DateTime;
    std::string _Username;
    std::string _Password;
    int _Permissions;

public:
    // Setters
    void SetDateTime(const std::string& dateTime) { _DateTime = dateTime; }
    void SetUsername(const std::string& username) { _Username = username; }
    void SetPassword(const std::string& password) { _Password = password; }
    void SetPermissions(int permissions) { _Permissions = permissions; }

    // Getters
    std::string GetDateTime() const { return _DateTime; }
    std::string GetUsername() const { return _Username; }
    std::string GetPassword() const { return _Password; }
    int GetPermissions() const { return _Permissions; }

    // __declspec(property)
    __declspec(property(get = GetDateTime, put = SetDateTime)) std::string DateTime;
    __declspec(property(get = GetUsername, put = SetUsername)) std::string Username;
    __declspec(property(get = GetPassword, put = SetPassword)) std::string Password;
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
};

