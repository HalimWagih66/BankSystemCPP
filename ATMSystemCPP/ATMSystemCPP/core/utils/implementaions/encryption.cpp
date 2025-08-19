#include "../headers/encryption.h"
#include <string>
using namespace std;
// Decrypts a given text using a simple encryption key (default = 2)
string Encryption::DecryptText(string Text, short EncryptionKey) {
	for (int i = 0; i < Text.length(); i++)
	{

		Text[i] = char((int)Text[i] - EncryptionKey);

	}
	return Text;
}
// Encrypts a given text using a simple encryption key (default = 2)
string Encryption::EncryptText(string Text, short EncryptionKey) {
	for (int i = 0; i < Text.length(); i++)
	{

		Text[i] = char((int)Text[i] + EncryptionKey);

	}

	return Text;
}