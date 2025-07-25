#include <string>
#include "messages.h"
#include <iostream>
#include "../../utils/headers/console_helper.h"
const std::string Messages::kEnterPhone = "Please enter a Phone Number: ";

const std::string Messages::kInvalidPhone = "Invalid Phone Number, Please enter a valid phone number: ";

const std::string Messages::kEnterEmail = "Please enter an email: ";

const std::string Messages::kInvalidEmail =
"\nInvalid email address.\n"
"Email must be in the correct format and from known domains (e.g., gmail.com, yahoo.com).\n"
"Please enter a valid email: ";

const std::string Messages::kEnterPassword = "Please Enter Your Password : ";

const std::string Messages::kEnterPin = "Please Enter Your Pin Code : ";

const std::string Messages::kEnterBalance = "Please Enter Your Balance : ";

const std::string Messages::kInvalidBalance = "Please Enter Your Balance : ";

const std::string Messages::kInvalidPin =
"\nInvalid PIN code.\n"
"A PIN code must be exactly 4 or 6 digits.\n"
"Please enter a pin code: ";

const std::string Messages::kPermissionFullAccess = "Do you want to give full access  (Y/N) ? ";
const std::string Messages::kPermissionPrompt = "Do You Want to give access to : \n\n";

const std::string Messages::kInvalidAccountNumber = "Invalid Account Number.\n"
"Account Number must contain exactly 10 digits.\n"
"Please enter a valid Account Number: ";

const std::string Messages::kInvalidPassword = "Invalid Password! Your Password must meet the following requirements\n"
    "- At least 8 characters\n"
    "- At least one uppercase letter (A ~ Z)\n"
    "- At least one lowercase letter (a ~ z)\n"
    "- At least one special character (e.g. @, #, $, !)\n\n"
    "Please Enter Valid Password : ";

const std::string Messages::kInvalidUsername = 
"Invalid Username! Please follow the rules below:\n"
"- Must be between 4 and 20 characters\n"
"- Must start with a letter (A ~ Z or a ~ z)\n"
"- Cannot contain spaces or symbols (only '.' or '_' are allowed)\n"
"- '.' or '_' can be used, but only once in total\n\n"
"Please enter a valid username: ";

const std::string Messages::kInvalidNumber = "Invalid number, please enter the number again: ";

const std::string Messages::kNumberOutOfRange = "Number is not within range, please enter the number again: ";

const std::string Messages::kPromptEnterNumber = "Please enter a number: ";

void Messages::ShowAccessDeniedMessage(){
    ConsoleHelper::ClearScreen();
    std::cout << "\n\n---------------------------------------------\n";
    std::cout << "Access Denied,\n";
    std::cout << "You Don't Have Permission To Do This,\n";
    std::cout << "Please Contact Your Admin\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Press any key to return to the Main menu...";
    system("pause>nul");
}