#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <iostream>
#include <unordered_set>
#include "../headers/string_utils.h"
using namespace std;

// Splits a string by a given delimiter and returns a vector of words
vector<string> StringUtils::SplitString(string line, string delim) {
    short pos = 0;
    string sWord;
    vector<string> vString;

    // Keep splitting while the delimiter is found
    while ((pos = line.find(delim)) != std::string::npos) {
        sWord = line.substr(0, pos);
        if (sWord != "") {
            vString.push_back(sWord);
        }
        line.erase(0, pos + delim.length());
    }

    // Add the remaining part of the string if it's not empty
    if (line != "") {
        vString.push_back(line);
    }

    return vString;
}

// Reverses the order of words in a string
string StringUtils::ReverseString(string line) {
    vector<string> seperate = SplitString(line, " ");
    string RevString = "";
    for (short i = seperate.size() - 1; i != -1; i--) {
        RevString += seperate[i] + " ";
    }
    return RevString;
}

// Removes trailing spaces from the right side of a string
string StringUtils::TrimRight(string line) {
    for (short i = line.length() - 1; i != -1; i--) {
        if (line[i] != ' ')
            return line.substr(0, i + 1);  // include the last non-space character
    }
    return "";
}

// Removes leading spaces from the left side of a string
string StringUtils::TrimLeft(string line) {
    for (short i = 0; i < line.size(); i++) {
        if (line[i] != ' ')
            return line.substr(i);  // return from first non-space
    }
    return "";
}

// Removes both leading and trailing spaces
string StringUtils::TrimString(string line) {
    line = TrimLeft(line);
    line = TrimRight(line);
    return line;
}

// Checks if a character is a vowel (A, E, I, O, U)
bool StringUtils::IsVowel(char ch) {
    const std::array<char, 5> VowelsChars = { 'A','E' , 'I', 'O','U' };
    ch = toupper(ch);
    for (char letter : VowelsChars) {
        if (ch == letter) {
            return true;
        }
    }
    return false;
}

// Returns a vector of vowels found in the input string
vector<char> StringUtils::GetVowels(string line) {
    cout << "Vowels in String are : ";
    vector<char> Vowels;
    for (size_t i = 0; i < line.size(); i++) {
        if (IsVowel(line[i])) {
            Vowels.push_back(line[i]);
        }
    }
    return Vowels;
}

// Counts lowercase characters in the string
short StringUtils::CountLowerCaseInString(string line) {
    short CountLowerCase = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (islower(line[i])) {
            CountLowerCase++;
        }
    }
    return CountLowerCase;
}

// Counts uppercase characters in the string
short StringUtils::CountUpperCaseInString(string line) {
    short CountUpperCase = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (isupper(line[i])) {
            CountUpperCase++;
        }
    }
    return CountUpperCase;
}

// Counts letters based on the enum value (all, uppercase, lowercase)
short StringUtils::CountLetters(string line, enLetterCountType WhatToCount) {
    if (WhatToCount == enLetterCountType::AllLetters) {
        return line.length();
    }

    short count = 0;
    for (size_t i = 0; i < line.length(); i++) {
        if (WhatToCount == enLetterCountType::SmallLetters && islower(line[i])) {
            count++;
        }
        if (WhatToCount == enLetterCountType::CapitalLetters && isupper(line[i])) {
            count++;
        }
    }
    return count;
}

// Converts the whole string to uppercase
string StringUtils::ToUpperCase(string Sentance) {
    for (size_t i = 0; i < Sentance.size(); i++) {
        Sentance[i] = toupper(Sentance[i]);
    }
    return Sentance;
}

// Converts the whole string to lowercase (by reference)
void StringUtils::ToLowerCase(string& Sentance) {
    for (size_t i = 0; i < Sentance.size(); i++) {
        Sentance[i] = tolower(Sentance[i]);
    }
}

// Inverts the case of a character (uppercase to lowercase or vice versa)
char StringUtils::InvertLetter(char letter) {
    return isupper(letter) ? tolower(letter) : toupper(letter);
}

// Inverts the case of all characters in a string (by reference)
void StringUtils::InvertString(string& text) {
    for (size_t i = 0; i < text.size(); i++) {
        text[i] = InvertLetter(text[i]);
    }
}

// Removes punctuation characters from a string
string StringUtils::RemovePunctuations(string text) {
    string S2 = "";
    for (size_t i = 0; i < text.size(); i++) {
        if (!ispunct(text[i])) {
            S2.push_back(text[i]);
        }
    }
    return S2;
}

// Replaces all matching words in a string with another word (case sensitive or insensitive)
string StringUtils::ReplaceWordInString(string line, string find, string replace, bool IsMatchCase) {
    vector<string> separate = SplitString(line, " ");
    string lineAfterReplace = "";

    for (string& word : separate) {
        if (IsMatchCase) {
            lineAfterReplace += (word == find ? replace : word) + " ";
        }
        else {
            lineAfterReplace += (ToUpperCase(word) == ToUpperCase(find) ? replace : word) + " ";
        }
    }

    return lineAfterReplace;
}

// Counts the number of words in a string
short StringUtils::CountWordsInString(string line) {
    string delim = " ";
    short pos = 0;
    short count = 0;
    string sWord;

    while ((pos = line.find(delim)) != std::string::npos) {
        sWord = line.substr(0, pos);
        if (sWord != "") {
            count++;
        }
        line.erase(0, pos + delim.length());
    }

    if (line != "") {
        count++;
    }

    return count;
}

// Checks if the string contains at least one uppercase letter
bool StringUtils::HasUpperCase(const string& word) {
    for (const char& Char : word) {
        if (isupper(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one lowercase letter
bool StringUtils::HasLowerCase(const string& word) {
    for (const char& Char : word) {
        if (islower(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one special (punctuation) character
bool StringUtils::HasSpecialCharacter(const string& word) {
    for (const char& Char : word) {
        if (ispunct(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one numeric digit
bool StringUtils::HasNumber(const string& word) {
    for (const char& Char : word) {
        if (isdigit(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one space character
bool StringUtils::HasSpace(const string& word) {
    for (char Char : word) {
        if (isspace(Char))
            return true;
    }
    return false;
}

// Checks if a word contains only letters and at most one dot or underscore
bool StringUtils::IsAlphaNameWithOneDotOrUnderscore(const string& word) {
    short sepCount = 0;

    for (char c : word) {
        if (isalpha(c))
            continue;

        if (c == '.' || c == '_') {
            if (++sepCount > 1)
                return false;
        }
        else {
            return false;
        }
    }

    return true;
}

// Counts how many digits are in a given string
short StringUtils::CountDigitsInWord(const string& AccountNumber) {
    short count = 0;
    for (char ch : AccountNumber) {
        if (isdigit(ch)) {
            count++;
        }
    }
    return count;
}

// Checks if the entire string consists of digits only
bool StringUtils::IsAllDigits(const string& AccountNumber) {
    for (char ch : AccountNumber) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return !AccountNumber.empty();
}

// Checks if a string contains only alphabetic letters and spaces
bool StringUtils::ContainsOnlyLettersAndSpaces(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

// Checks if a string contains only alphabetic letters
bool StringUtils::IsAlphaOnly(const std::string& text)
{
    for (const char& ch : text) {
        if (!isalpha(ch))
            return false;
    }
    return !text.empty();
}

// Converts a number to its English text representation
string StringUtils::NumberToText(int Number)
{

    if (Number == 0)
    {
        return "";
    }

    if (Number >= 1 && Number <= 19)
    {
        string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
    "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
      "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

        return  arr[Number] + " ";

    }

    if (Number >= 20 && Number <= 99)
    {
        string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
        return  arr[Number / 10] + " " + NumberToText(Number % 10);
    }

    if (Number >= 100 && Number <= 199)
    {
        return  "One Hundred " + NumberToText(Number % 100);
    }

    if (Number >= 200 && Number <= 999)
    {
        return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
    }

    if (Number >= 1000 && Number <= 1999)
    {
        return  "One Thousand " + NumberToText(Number % 1000);
    }

    if (Number >= 2000 && Number <= 999999)
    {
        return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
    }

    if (Number >= 1000000 && Number <= 1999999)
    {
        return  "One Million " + NumberToText(Number % 1000000);
    }

    if (Number >= 2000000 && Number <= 999999999)
    {
        return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
    }

    if (Number >= 1000000000 && Number <= 1999999999)
    {
        return  "One Billion " + NumberToText(Number % 1000000000);
    }
    else
    {
        return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
    }

}