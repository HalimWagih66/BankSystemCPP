#include "../headers/big_number_utils.h"
// Increment a large number represented as a string by 1
// Handles carry-over correctly (e.g., "129" -> "130", "999" -> "1000")
// Preserves leading zeros if any (except when rolling over all digits)
std::string BigNumberUtils::IncrementByOne(std::string number)
{
    int sizeString = number.size();

    // Traverse the string from the last digit to the first
    for (int i = sizeString - 1; i >= 0; i--)
    {
        // If current digit is less than or equal to '8', just increment it and return
        if (number[i] <= '8') {
            number[i] += 1;  // Increment the character digit by 1
            return number;
        }
        else
            // If digit is '9', set current digit to '0' and carry over to next digit
            number[i] = '0';
    }

    // If all digits were '9', then after the loop, prepend '1' to the number
    // e.g., "999" becomes "1000"
    return "1" + number;
}