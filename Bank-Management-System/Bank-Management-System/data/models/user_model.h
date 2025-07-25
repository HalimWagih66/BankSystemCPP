#pragma once
#include "person_model.h"
#include <iostream>
#include <cmath>
class UserModel : public PersonModel {
private:
    short _Permissions;
    std::string _Password;
    std::string _Username;
    bool _MarkedForDelete = false;


public:
    UserModel(std::string FirstName, std::string LastName,
        std::string Email, std::string Phone, std::string UserName, std::string Password,
        int Permissions) :
        PersonModel(FirstName, LastName, Email, Phone)

    {
        _Username = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }
    UserModel() :
        PersonModel("", "", "", "")

    {
        _Username = "";
        _Password = "";
        _Permissions = 0;
    }
    bool isEmpty() {
        return (_Username.empty() && _Password.empty() && _Permissions == 0 &&
			FirstName.empty() && LastName.empty() && Email.empty() && PhoneNumber.empty());
    }
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128,CurrencyExchange = 256
    };
    std::string GetUserName()const
    {
        return _Username;
    }

    void SetUserName(std::string UserName)
    {
        _Username = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) std::string Username;

    void SetPassword(std::string Password)
    {
        _Password = Password;
    }

    std::string GetPassword()const
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) std::string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()const
    {
        return _Permissions;
    }

    __declspec(property(get = GetMarkedForDelete, put = SetMarkedForDelete)) bool MarkedForDelete;

    bool GetMarkedForDelete()const {
        return _MarkedForDelete;
    }
    void SetMarkedForDelete(bool Delete) {
        _MarkedForDelete = Delete;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    void PrintUser()const
    {
        std::cout << "\nUser Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << FirstName;
        std::cout << "\nLastName    : " << LastName;
        std::cout << "\nFull Name   : " << GetFullName();
        std::cout << "\nEmail       : " << Email;
        std::cout << "\nPhone       : " << PhoneNumber;
        std::cout << "\nUser Name   : " << Username;
        std::cout << "\nPassword    : " << Password;
        std::cout << "\nPermissions : " << Permissions;
        std::cout << "\n___________________\n";
    }
    bool CheckAccessPermission(const int& Permission) const{
        if (Permissions == -1)return true;
        if ((Permissions & Permission) == Permission)
        {
            return true;
        }
        return false;
    }
};