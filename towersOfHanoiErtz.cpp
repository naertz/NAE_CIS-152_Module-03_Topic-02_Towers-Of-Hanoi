// =================================================================================================
// Name             : Towers Of Hanoi Demonstration
// Author           : Noah Allan Ertz
// Created          : 09/18/2021
// Course           : CIS 152 - Data Structures
// Version          : 1.1
// OS               : Windows 10
// IDE              : Qt 5.12.5
// Copyright        : This is my own original work based on specifications issued by our instructor.
// Description      : Calculates number of moves in Towers of Hanoi given a number of disks.
//                    Input:  Number of disks
//                    Output: Message of number of disks requiring a certain number of moves
// Academic Honesty : I attest that this is my original work. I have not used unauthorized source
//                    code, either modified or unmodified. I have not given other fellow students
//                    access to my program.
// =================================================================================================

/**
 * Recursion is the process of a function calling itself within itself.
 * A function alpha calls itself, leading to function beta (from the second function call) calling original function alpha.
 * There must be at least one base criteria or condition that is met to allow the function to stop calling itself recursively.
 * The recursive calls progress in a way that each time a recursive call is made, the base criteria draws near.
 */

/**
 * The recursion in the program below has a base criteria of number of disks being greater than 0, in which case the condition is not met and the count is returned.
 * The program begins by starting with given number of disks. The program recursively goes down from the first call until number of disks is 0, in which case count is 0.
 * Then the program goes back the previous recursive call, which increments the count by 1, and count is then incremented by the returned value of recursive function call.
 * The above starts creating a pattern where count is incremented as so:
 * 1 + 0 = 1
 * 2 + 1 = 3
 * 4 + 3 = 7
 * 8 + 7 = 15
 * 16 + 15 = 31
 * ...
 * Eventually the last returned value is reached, indicating the total number of moves required to perform Towers of Hanoi with a given number of disks.
 * The formula demonstrated can be represented as (2 ^ n) - 1.
 */

#include <climits>
#include <cstdlib>
#include <errno.h>
#include <iostream>

// Enumeration for string to integer validation
enum stringToIntegerError { STRTOINT_SUCCESS, STRTOINT_OVERFLOW, STRTOINT_UNDERFLOW, STRTOINT_INCONVERTIBLE };

// Constants for mininum and maximum valid integer values
const int MIN_VALUE = 0;
const int MAX_VALUE = 31;

// Constant for invalid value
const int INVALID_VALUE = -1;

stringToIntegerError stringToIntegerValidation (int &parsedInteger, const char *stringInputPointer, int base = 0);
int getValidInteger(std::string stringInput, int minValue = MIN_VALUE, int maxValue = MAX_VALUE);
int performTowersOfHanoiMove(int numberOfDisks);

int main() {
    // String input
    std::string stringInput;
    // Integer to parse
    int inputNumber;

    // Execute until a valid integer is parsed.
    do {
        // Prompt user.
        std::cout << "Please enter the number of disks: " << std::flush;
        // Get string input.
        std::getline(std::cin, stringInput);
        // Get validated integer.
        inputNumber = getValidInteger(stringInput);
    } while (inputNumber == INVALID_VALUE);

    // Calculate total number of moves to perform towers of hanoi with input number of disks.
    int numberOfMoves = performTowersOfHanoiMove(inputNumber);
    // Print message of calculation.
    std::cout << inputNumber << " disk(s) require(s) " << numberOfMoves << " move(s)" << std::endl;

    // Exit program successfully.
    return 0;
}

/**
 * @brief stringToIntegerValidation parses an integer from a string and returns the error result.
 * @param parsedInteger = Integer to receive parsed result passed by reference
 * @param stringInputPointer = Passed pointer to null-terminated byte string constant to be interpreted
 * @param base = Integer to determine base of integer passed by value (default to 0 for auto-detected base)
 * @return = stringToIntegerError enum representing the validation result from parsing string to integer
 */

stringToIntegerError stringToIntegerValidation (int &parsedInteger, const char *stringInputPointer, int base) {
    // Error result to return
    stringToIntegerError errorResult;
    // Pointer to pointer of character past the last character interpreted
    char *end;
    // Long to parse from string and to be cast to integer after validation
    long longToParse;
    // A preprocesor macro initialized to 0 for upcoming validation. In this case, it is used to determine if the long receives a value that is out of range.
    errno = 0;
    // Interpret integer value from byte string pointed to by the stringInputPointer.
    longToParse = std::strtol(stringInputPointer, &end, base);

    // Determine if errno is out of range AND long returns LONG_MAX (the maximum value of a long) OR long exceeds INT_MAX (the maximum value of an integer). Upon error, long returns 0.
    if ((errno == ERANGE && longToParse == LONG_MAX) || longToParse > INT_MAX) {
        errorResult = STRTOINT_OVERFLOW;
    } else if ((errno == ERANGE && longToParse == LONG_MIN) || longToParse < INT_MIN) { // Determine if errno is out of range AND long returns LONG_MIN (the minimum value of a long) OR long exceeds INT_MIN (the minimum value of an integer). Upon error, long returns 0.
        errorResult = STRTOINT_UNDERFLOW;
    } else if (*stringInputPointer == '\0' || *end != '\0') { // Determine if byte string or character pointer of last pointer returns null. Prevents output such as "5g".
        errorResult = STRTOINT_INCONVERTIBLE;
    } else { // Input is a valid integer.
        errorResult = STRTOINT_SUCCESS;
        // Cast valid long to integer.
        parsedInteger = static_cast<int>(longToParse);
    }

    // Return error result.
    return errorResult;
}

/**
 * @brief stringToInteger takes a given string and attempts to parse and return an integer. Upon error, integer is 0.
 * @param stringInput = Input string to be parsed
 * @param minValue = Minimum valid integer value
 * @param maxValue = Maximum valid integer value
 * @return = an integer parsed from the input string
 */

int getValidInteger(std::string stringInput, int minValue, int maxValue) {
    // Convert string to c-string and then convert to constant byte string to pass to validation function.
    const char * stringInputPointer = stringInput.c_str();

    // Declare integer to pass by reference and to store parsed result from input string.
    int integerFromString = INVALID_VALUE;

    // Call validation function and store error result to enum variable.
    stringToIntegerError errorResult = stringToIntegerValidation(integerFromString, stringInputPointer);

    // Determine error result.
    if (errorResult == STRTOINT_OVERFLOW) {
        // Print message informing user that input is too high (e.g. "99999999999999999999999999999999999999").
        std::cout << "Input is too high. Please enter an integer between " << minValue << " and " << maxValue << "." << std::endl;
    } else if (errorResult == STRTOINT_UNDERFLOW) {
        // Print message informing user that input is too low (e.g. "-11111111111111111111111111111111111111").
        std::cout << "Input is too low. Please enter an integer between " << minValue << " and " << maxValue << "." << std::endl;
    } else if (errorResult == STRTOINT_INCONVERTIBLE) {
        // Print message informing user that input is not a valid integer (e.g., "5g", "-5g", "9 9").
        std::cout << "Invalid input. Please enter an integer." << std::endl;
    } else if (integerFromString > maxValue) {
        // Print message informing user that input is too high (e.g. maxValue + 1).
        std::cout << "Too many moves to output. Please enter an integer between " << minValue << " and " << maxValue << "." << std::endl;
        // Reassign parsed integer to invalid value.
        integerFromString = INVALID_VALUE;
    } else if (integerFromString < minValue) {
        // Print message informing user that input is too low (e.g. minValue - 1).
        std::cout << "Cannot have negative number of disks. Please enter an integer between " << minValue << " and " << maxValue << "." << std::endl;
        // Reassign parsed integer to invalid value.
        integerFromString = INVALID_VALUE;
    }

    // Returns parsed integer.
    return integerFromString;
}

/**
 * @brief performTowersOfHanoiMove calculates the total required number of moves to perform Towers of Hanoi given a number of disks.
 * @param numberOfDisks = Number of disks for Towers of Hanoi game
 * @return = Total required number of moves to perform Towers of Hanoi
 */

int performTowersOfHanoiMove(int numberOfDisks) { // Source, Destination, Auxiliary
    int count = 0;

    if (numberOfDisks > 0) {
        count = performTowersOfHanoiMove(numberOfDisks - 1);  // Source -> Auxiliary, Destination
        ++count;
        count += performTowersOfHanoiMove(numberOfDisks - 1); // Auxiliary -> Destination, Source
    }

    return count;
}
