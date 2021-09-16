// =================================================================================================
// Name             : Towers Of Hanoi Demonstration
// Author           : Noah Allan Ertz
// Created          : 09/15/2021
// Course           : CIS 152 - Data Structures
// Version          : 1.0
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
 * Eventually the last returned value is reached, indicating the total number of moves required to perform Towers of Hanoi with a given number of disks. The formula demonstrated can be represented as (2 ^ n) - 1.
 */

#include <iostream>
#include <vector>

int performTowersOfHanoiMove(int numberOfDisks);

int main() {
    // Prompt user.
    std::cout << "Please enter the number of disks: " << std::flush;
    // Variable for integer input
    int inputNumber;
    // Get input.
    std::cin >> inputNumber;
    // Calculate total number of moves to perform towers of hanoi with input number of disks.
    int numberOfMoves = performTowersOfHanoiMove(inputNumber);
    // Print message of calculation.
    std::cout << inputNumber << " disk(s) require(s) " << numberOfMoves << " moves" << std::endl;
}

int performTowersOfHanoiMove(int numberOfDisks) { // Source, Destination, Auxiliary
    int count = 0;
    if (numberOfDisks > 0) {
        count = performTowersOfHanoiMove(numberOfDisks - 1);  // Source -> Auxiliary, Destination
        ++count;
        count += performTowersOfHanoiMove(numberOfDisks - 1); // Auxiliary -> Destination, Source
    }
    return count;
}
