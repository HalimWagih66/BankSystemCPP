#pragma once
#include <string>
class Messages {
public:
    static const std::string kEnterPhone;
    static const std::string kInvalidPhone;
    static const std::string kEnterEmail;
    static const std::string kInvalidEmail;
    static const std::string kEnterPassword;
    static const std::string kInvalidPin;
	static const std::string kEnterPin;
    static const std::string kEnterBalance;
    static const std::string kInvalidBalance;
    static const std::string kInvalidAccountNumber;

    static const std::string kInvalidUsername;
    static const std::string kPermissionFullAccess;
    static const std::string kPermissionPrompt;

    static const std::string kInvalidPassword;

    static const std::string kInvalidNumber;
    static const std::string kNumberOutOfRange;
    static const std::string kPromptEnterNumber;

    static void ShowAccessDeniedMessage();
};