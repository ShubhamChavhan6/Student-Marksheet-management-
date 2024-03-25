#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

 const string filename = "records.csv";

int ValidIntInput(const std::string& prompt, int minValid, int maxValid) {
    int userInput;
    while (true) {
        std::cout << prompt;
        if (std::cin >> userInput) {
            // Input is an integer
            if (userInput >= minValid && userInput <= maxValid) {
                // Input is within the specified range
                break;
            }
            else {
                std::cout << "Invalid input. Please enter a number between " << minValid << " and " << maxValid << ". \n" << std::endl;
            }
        }
        else {
            // Input is not an integer
            std::cout << "Invalid input. Please enter a valid number. \n" << std::endl;
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining characters
        }
    }
    return userInput;
}

// Function to get marks for a subject with input validation
int getSubjectMarks(const std::string& subjectName) {
    int marks;
    while (true) {
        std::cout << "Enter " << subjectName << " Marks: ";
        if (std::cin >> marks) {
            if (marks >= 0 && marks <= 100) {
                break; // Break out of the loop if the input is valid
            }
            else {
                std::cout << "Out of range. Please enter " << subjectName << " marks between 0 and 100. \n" << std::endl;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number between 0 and 100. \n" << std::endl;
        }
    }
    return marks;
}


int PositiveInt(const string& prompt) {
    int num;
    while (true) {
        cout << prompt;
        if (cin >> num && num > 0) 
        {
            if (num > 10) {
                cout << " Max 10 records can be added at a time.";
            }
            break; // Valid input, exit the loop.
        }
        cin.clear(); // Clear error flags.
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input.
        cerr << "Invalid input. Please enter a positive Number." << endl;
    }
    cin.ignore(); // Clear newline from the input buffer.
    return num;
}

bool ValidRollNum(int &rollNum) 
{
    if (cin >> rollNum && rollNum >= 1 && rollNum <= 100)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        return true; // Valid input
    }
    else
    {
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        return false; // Invalid input, return false
    }
}

bool RollNumExists(int &rollNum) {
    ifstream inputFile(filename);
    string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string studentName;
        int existingRollNum;

        if (getline(iss, studentName, ',') && (iss >> existingRollNum)) {
            if (existingRollNum == rollNum) {
                inputFile.close();
                return true; // Roll number already exists
            }
        }
    }
    inputFile.close();
    return false; // Roll number doesn't exist
}

string capitalizeWord(const string& input) {
    string result = input; // Make a copy of the input string

    // Capitalize the first letter of each word
    bool newWord = true; // Flag to indicate the start of a new word
    for (char& c : result) {
        if (newWord && isalpha(c)) {
            c = toupper(c); // Capitalize the first letter of the word
            newWord = false; // Reset the flag
        }
        else if (isspace(c)) {
            newWord = true; // Set the flag for the next word
        }
    }

    return result;
}

bool markSheetExists(int rollToCheck) {
    std::ifstream inputFile("marksheet.csv");
    if (!inputFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int rollNum;
        char comma;

        if (iss >> rollNum >> comma) {
            if (rollNum == rollToCheck) {
                inputFile.close();
                return true; // Mark sheet exists
            }
        }
    }

    inputFile.close();
    return false; // Mark sheet does not exist
}

bool isValidName(const std::string& name) {
    // Check if the name is not empty
    if (name.empty()) {
        std::cout << "Invalid input. Name cannot be empty." << std::endl;
        return false;
    }

    // Check if the name contains at least one non-digit character
    for (char c : name) {
        if (!std::isdigit(c)) {
            return true; // At least one non-digit character found, valid name
        }
    }

    std::cout << "Invalid input. Name must contain at least one non-digit character." << std::endl;
    return false; // All characters are digits, not a valid name
}
