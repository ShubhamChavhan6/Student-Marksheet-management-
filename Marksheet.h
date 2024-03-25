
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include "input_valid.h"
#include "password-color.h"

#undef max

struct MarkSheetRecord {
    std::string StudentName;
    int RollNum;
    int EnglishMarks;
    int PhysicsMarks;
    int ChemistryMarks;
    int MathMarks;
    int ComputerMarks;
};

const std::string marksfilename = "marksheet.csv";

// Function to insert a marksheet record into the CSV file
void insertMarkSheetRecord(std::ofstream& file, const MarkSheetRecord& record) {
    file << record.RollNum << "," << record.StudentName << ","
        << record.EnglishMarks << "," << record.PhysicsMarks << ","
        << record.ChemistryMarks << "," << record.MathMarks << ","
        << record.ComputerMarks << "\n";
}

int createMarkSheet() {
    std::ofstream outputFile(marksfilename, std::ios::app);

    if (!outputFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    int numRecords = ValidIntInput(" Enter the number of records to add: ", 1, 10); // Validate the number of records

    std::cin.ignore(); // Clear the newline character from the input buffer

    for (int i = 0; i < numRecords; ++i) {
        MarkSheetRecord record;

        std::cout << "\nEnter Student name for record " << i + 1 << ": ";
        std::getline(std::cin, record.StudentName);
        record.StudentName = capitalizeWord(record.StudentName);
        
        record.RollNum = ValidIntInput("Enter Student Roll (1-100) for record " + std::to_string(i + 1) + ": ", 1, 100);

        // Get marks for each subject using the function
        record.EnglishMarks = getSubjectMarks("English");
        record.PhysicsMarks = getSubjectMarks("Physics");
        record.ChemistryMarks = getSubjectMarks("Chemistry  ");
        record.MathMarks = getSubjectMarks("Mathematics");
        record.ComputerMarks = getSubjectMarks("Computer   ");

        insertMarkSheetRecord(outputFile, record);

        std::cout << "Marksheet record successfully added." << std::endl;

        if (i < numRecords - 1) {
            // If there are more records to add, show a separator message
            std::cout << "-----------------------------------" << std::endl;
            std::cin.ignore();
        }
    }

    return 0;
}

bool DeleteMarkSheet() {
    int rollToDelete;

    do {
        std::cout << "\nEnter the roll number of the student to delete : ";

        if (!(std::cin >> rollToDelete)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
        }

        else if (rollToDelete < 1 || rollToDelete > 100) {
            std::cout << "Roll number should be between 1 and 100. Please try again." << std::endl;
        }

        else if (!markSheetExists(rollToDelete)) {
            std::cout << "Student record with Roll Number " << rollToDelete << " does not exist. Please try again." << std::endl;
        }

        else {
            break; // Valid roll number and it exists, break out of the loop
        }

    } while (true);

    std::ifstream inputFile(marksfilename);

    if (!inputFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }

    std::ofstream tempFile("temp_records.csv");

    if (!tempFile) {
        std::cerr << "Error creating temporary file." << std::endl;
        inputFile.close();
        return false;
    }

    bool found = false;
    std::string line;

    while (std::getline(inputFile, line)) {
        MarkSheetRecord record;
        size_t commaPos = line.find(",");
        if (commaPos != std::string::npos) {
            record.StudentName = line.substr(commaPos + 1);
            record.RollNum = std::stoi(line.substr(0, commaPos));
            if (record.RollNum == rollToDelete) {
                found = true;
            }
            else {
                tempFile << line << "\n";
            }
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        if (remove(marksfilename.c_str()) != 0) {
            std::cerr << "Error: Unable to remove the original file." << std::endl;
            return false; // Handle the error appropriately
        }
        if (rename("temp_records.csv", marksfilename.c_str()) != 0) {
            std::cerr << "Error: Unable to rename the temporary file." << std::endl;
            return false; // Handle the error appropriately
        }
        std::cout << "Student record with Roll Number " << rollToDelete << " deleted." << std::endl;
        return true;
    }
    else {
        std::cout << "Student record with Roll Number " << rollToDelete << " not found." << std::endl;
        if (remove("temp_records.csv") != 0) {
            std::cerr << "Error: Unable to remove the temporary file." << std::endl;
            // Handle the error appropriately
        }
        return false;
    }
}

bool updateMarksheet() {
    int rollToUpdate;

    while (true) {
        std::cout << "\nEnter the Roll Number of the student to update: ";

        if (ValidRollNum(rollToUpdate)) {
            break; // Valid input, break out of the loop
        }
        else {
            std::cout << "Invalid input. Please enter a valid roll number between 1 and 100." << std::endl;
        }
    }

    std::ifstream inputFile(marksfilename);

    if (!inputFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }

    std::vector<MarkSheetRecord> records;
    std::string line;

    // Read all records into a vector
    while (std::getline(inputFile, line)) {
        MarkSheetRecord record;
        std::istringstream iss(line);
        char comma;

        if (iss >> record.RollNum >> comma
            && std::getline(iss, record.StudentName, ',')
            && iss >> record.EnglishMarks >> comma
            && iss >> record.PhysicsMarks >> comma
            && iss >> record.ChemistryMarks >> comma
            && iss >> record.MathMarks >> comma
            && iss >> record.ComputerMarks) {
            records.push_back(record);
        }
    }

    inputFile.close();

    bool found = false;

    // Find and update the record
    for (MarkSheetRecord& record : records) {
        if (record.RollNum == rollToUpdate) {
            found = true;

            // Prompt the user for updated data
            std::cout << "Enter Student Name: ";

            std::string userInputName;
            while (true) {
                std::getline(std::cin, userInputName);

                if (isValidName(userInputName)) {
                    break; // Valid name, break out of the loop
                }
                else {
                    std::cout << "\n Enter Student Name: "; // Re-prompt for input
                }
            }

            // Call the capitalizeWord function to capitalize the name
            record.StudentName = capitalizeWord(userInputName);


            record.EnglishMarks = getSubjectMarks("New English");
            record.PhysicsMarks = getSubjectMarks("New Physics");
            record.ChemistryMarks = getSubjectMarks("New Chemistry");
            record.MathMarks = getSubjectMarks("New Mathematics");
            record.ComputerMarks = getSubjectMarks("New Computer");

            // Break the loop since we found and updated the record
            break;
        }
    }

    if (found) {
        // Reopen the file for writing (truncating existing data)
        std::ofstream outputFile(marksfilename);

        if (!outputFile) {
            std::cerr << "Error opening file for writing." << std::endl;
            return false;
        }

        // Write the updated records back to the file
        for (const MarkSheetRecord& record : records) {
            outputFile << record.RollNum << ","
                << record.StudentName << ","
                << record.EnglishMarks << ","
                << record.PhysicsMarks << ","
                << record.ChemistryMarks << ","
                << record.MathMarks << ","
                << record.ComputerMarks << "\n";
        }

        outputFile.close();
        std::cout << "Record with Roll Number " << rollToUpdate << " updated successfully." << std::endl;
    }
    else {
        std::cout << "Student record with Roll Number " << rollToUpdate << " not found." << std::endl;
    }

    return found;
}

int calculateTotalMarks(const MarkSheetRecord& record) {
    return record.EnglishMarks + record.PhysicsMarks + record.ChemistryMarks +
        record.MathMarks + record.ComputerMarks;
}

// Function to calculate the percentage for a record
double calculatePercentage(const MarkSheetRecord& record) {
    int totalMarks = calculateTotalMarks(record);
    return static_cast<double>(totalMarks) / 500.0 * 100.0;
}

// Function to determine the grade based on the percentage
std::string determineGrade(double percentage) {
    if (percentage >= 90) {
        return "A+";
    }
    else if (percentage >= 85) {
        return "A";
    }
    else if (percentage >= 75) {
        return "B+";
    }
    else if (percentage >= 70) {
        return "B";
    }
    else if (percentage >= 65) {
        return "C";
    }
    else if (percentage >= 55) {
        return "D";
    }
    else if (percentage >= 35) {
        return "E";
    }
    else {
        return "F"; // Failed
    }
}

// Function to determine pass or fail based on percentage
std::string determinePassFail(double percentage) {
    return (percentage >= 35.0) ? "Pass" : "Fail";
}

std::vector<std::string> getFailedSubjects(const MarkSheetRecord& record) {
    std::vector<std::string> failedSubjects;

    if (record.EnglishMarks < 40) {
        failedSubjects.push_back("English");
    }
    if (record.PhysicsMarks < 40) {
        failedSubjects.push_back("Physics");
    }
    if (record.ChemistryMarks < 40) {
        failedSubjects.push_back("Chemistry");
    }
    if (record.MathMarks < 40) {
        failedSubjects.push_back("Math");
    }
    if (record.ComputerMarks < 40) {
        failedSubjects.push_back("Computer");
    }

    return failedSubjects;
}

void displayRecord(const MarkSheetRecord& record) {
    std::cout << "\n-----------------------------" << std::endl;
    std::cout << "Roll Number: " << record.RollNum << std::endl;
    std::cout << "Student Name: " << record.StudentName << std::endl;
    std::cout << "\n----------------------------" << std::endl;
    std::cout << "Subject\t\tMarks" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "English\t\t" << record.EnglishMarks << std::endl;
    std::cout << "Physics\t\t" << record.PhysicsMarks << std::endl;
    std::cout << "Chemistry\t" << record.ChemistryMarks << std::endl;
    std::cout << "Math\t\t" << record.MathMarks << std::endl;
    std::cout << "Computer\t" << record.ComputerMarks << std::endl;
    std::cout << "-------------------------------" << std::endl;

    // Calculate the total marks and percentage
    int totalMarks = calculateTotalMarks(record);
    double percentage = calculatePercentage(record);

    std::cout << "Total Marks:\t" << totalMarks << std::endl;
    std::cout << "Percentage :\t" << percentage << "%" << std::endl;

    string grade = determineGrade(percentage);
    std::cout << "Grade  :\t" << grade << std::endl;

    std::string passFail = determinePassFail(percentage);
    std::cout << "Result :\t" << passFail << std::endl;

    std::vector<std::string> failedSubjects = getFailedSubjects(record);
    if (!failedSubjects.empty()) {
        std::cout << "Failed Subjects: ";
        for (const std::string& subject : failedSubjects) {
            std::cout << subject << ", ";
        }
        std::cout << std::endl;
    }
}

bool searchMarkSheet() {
    int rollToSearch;

    std::cout << "\nEnter the Roll Number to search: ";
    std::cin >> rollToSearch;

    std::ifstream inputFile(marksfilename);

    if (!inputFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }

    bool found = false;
    std::string line;

    while (std::getline(inputFile, line)) {
        MarkSheetRecord record;
        std::istringstream iss(line);
        char comma;

        if (iss >> record.RollNum >> comma
            && std::getline(iss, record.StudentName, ',')
            && iss >> record.EnglishMarks >> comma
            && iss >> record.PhysicsMarks >> comma
            && iss >> record.ChemistryMarks >> comma
            && iss >> record.MathMarks >> comma
            && iss >> record.ComputerMarks) {
            if (record.RollNum == rollToSearch) {
                found = true;
                    
                displayRecord(record); // Where studentRecord is the MarkSheetRecord object to be displayed.
                break; 
            }
        }
    }

    inputFile.close();

    if (!found) {
        std::cout << "Student record with Roll Number " << rollToSearch << "does not exists" << std::endl;
    }

    return found;
}

int getScreenWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void showAllRecords() {
    std::ifstream inputFile(marksfilename);

    if (!inputFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    std::string line;
    int recordNumber = 1;

    int screenWidth = getScreenWidth(); // Get the current screen width
    int tableWidth = screenWidth - 10;

    // Display table headers
    std::cout << "\n ";       /* std::setfill('-') << std::setw(tableWidth) << "-" << std::setfill(' ') << std::endl;*/
    printColorfulText("All Mark Sheet Records:", COLOR_CYAN);
    std::cout << std::setfill('-') << std::setw(tableWidth) << "-" << std::setfill(' ') << std::endl;

    //std::cout << std::setw(10) << "Record#" << std::setw(15) << "Roll No."
    //    << std::setw(25) << "Students" << std::setw(15) << "English"
    //    << std::setw(15) << "Physics"  << std::setw(15) << "Chemistry"
    //    << std::setw(15) << "Maths"    << std::setw(15) << "Computer" 
    //    << std::setw(15) << "Total Marks" << std::setw(15) << "Percentage"
    //    << std::setw(10) << "Pass/Fail"   << std::endl;

    std::stringstream headerStream;

    // Format and add each header column to the stringstream
    headerStream << std::setw(5) << "Record#" << std::setw(10) << "Roll No."
        << std::setw(18) << "Students" << std::setw(20) << "English"
        << std::setw(15) << "Physics"  << std::setw(15) << "Chemistry"
        << std::setw(15) << "Maths"    << std::setw(15) << "Computer"
        << std::setw(15) << "Total Marks" << std::setw(15) << "Percentage" 
        << std::setw(10) << "Pass/Fail";

    // Pass the formatted string to printColorfulText
    printColorfulText(headerStream.str(), COLOR_YELLOW);

    std::cout << std::setfill('-') << std::setw(tableWidth) << "-" << std::setfill(' ') << std::endl;
    
    while (std::getline(inputFile, line)) {
        MarkSheetRecord record;
        std::istringstream iss(line);
        char comma;

        if (iss >> record.RollNum >> comma
            && std::getline(iss, record.StudentName, ',')
            && iss >> record.EnglishMarks >> comma
            && iss >> record.PhysicsMarks >> comma
            && iss >> record.ChemistryMarks >> comma
            && iss >> record.MathMarks >> comma
            && iss >> record.ComputerMarks) {

            int totalMarks = calculateTotalMarks(record);
            double percentage = calculatePercentage(record);
            std::string passFail = determinePassFail(percentage);

            // Display each record in a table row
            std::cout << std::setw(10) << recordNumber;
            std::cout << std::setw(15) << record.RollNum;
            std::cout << std::setw(25) << std::left << record.StudentName;
            std::cout << std::setw(18) << record.EnglishMarks;
            std::cout << std::setw(15) << record.PhysicsMarks;
            std::cout << std::setw(15) << record.ChemistryMarks;
            std::cout << std::setw(15) << record.MathMarks;
            std::cout << std::setw(15) << record.ComputerMarks;
            std::cout << std::setw(15) << totalMarks << std::fixed << std::setprecision(2) << std::setw(15) << percentage;
            std::cout << std::setw(10) << passFail << std::endl;
            recordNumber++;
        }
    }

    inputFile.close();
}
