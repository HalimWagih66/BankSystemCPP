#pragma once
#include <vector>
#include <string>

// Enum to specify which letter case type to count
enum class enLetterCountType
{
    SmallLetters = 0,
    CapitalLetters = 1,
    AllLetters = 2
};

class StringUtils
{
public:
    // Splits a string by a specific delimiter and returns a list of substrings
    static std::vector<std::string> SplitString(std::string line, std::string delim);

    // Reverses the entire string
    static std::string ReverseString(std::string line);

    // Removes spaces from the right side of the string
    static std::string TrimRight(std::string line);

    // Removes spaces from the left side of the string
    static std::string TrimLeft(std::string line);

    // Removes spaces from both sides of the string
    static std::string TrimString(std::string line);

    // Checks if a character is a vowel (a, e, i, o, u)
    static bool IsVowel(char character);

    // Returns all vowels found in the string
    static std::vector<char> GetVowels(std::string line);

    // Counts lowercase letters in the string
    static short CountLowerCaseInString(std::string line);

    // Counts uppercase letters in the string
    static short CountUpperCaseInString(std::string line);

    // Counts letters based on the specified type (small, capital, all)
    static short CountLetters(std::string line, enLetterCountType whatToCount = enLetterCountType::AllLetters);

    // Converts the entire string to uppercase
    static std::string ToUpperCase(std::string sentence);

    // Converts the entire string to lowercase (in-place)
    static void ToLowerCase(std::string& sentence);

    // Inverts the case of a single letter (A becomes a, b becomes B)
    static char InvertLetter(char letter);

    // Inverts the case of all letters in the string (in-place)
    static void InvertString(std::string& text);

    // Removes punctuation marks from the string
    static std::string RemovePunctuations(std::string text);

    // Replaces all occurrences of a word in the string with another, with optional case sensitivity
    static std::string ReplaceWordInString(std::string line, std::string find, std::string replace, bool isMatchCase = true);

    // Counts the number of words in the string
    static short CountWordsInString(std::string line);

    // Checks if the word contains at least one uppercase letter
    static bool HasUpperCase(const std::string& word);

    // Checks if the word contains at least one lowercase letter
    static bool HasLowerCase(const std::string& word);

    // Checks if the word contains any special character
    static bool HasSpecialCharacter(const std::string& word);

    // Checks if the word contains any digits
    static bool HasNumber(const std::string& word);

    // Checks if the word contains any whitespace
    static bool HasSpace(const std::string& word);

    // Validates that a username contains only letters and one dot or underscore
    static bool IsAlphaNameWithOneDotOrUnderscore(const std::string& Username);

    // Counts how many digits exist in the word
    static short CountDigitsInWord(const std::string& word);

    // Checks if the entire word is made of digits only
    static bool IsAllDigits(const std::string& word);

    // Checks if the string contains only letters and spaces (no digits or symbols)
    static bool ContainsOnlyLettersAndSpaces(const std::string& string);

    // Checks if the string contains only alphabetic characters
    static bool IsAlphaOnly(const std::string& text);

    // Converts a number to its English textual representation (example: 123 becomes "one hundred twenty-three")
    static std::string NumberToText(int number);
};
