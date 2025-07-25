#pragma once
#include <string>

class Encryption
{
public:
    // Decrypts a given text using a simple encryption key (default = 2)
    static std::string DecryptText(std::string text, short encryptionKey = 2);

    // Encrypts a given text using a simple encryption key (default = 2)
    static std::string EncryptText(std::string text, short encryptionKey = 2);
};
