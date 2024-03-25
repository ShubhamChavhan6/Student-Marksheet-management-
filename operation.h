#pragma once
#include "Input_valid.h"
#include <vector>
using namespace std;

struct Record {
    string StudentName;
    int RollNum=0;
};


void insertRecord(ofstream& file, const Record& record) {
    file << record.StudentName << "," << record.RollNum << "\n";
}

int addStudents() 
{
    ofstream outputFile(filename, ios::app);

    if (!outputFile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    const int maxRecords = 10; // Set the maximum number of records to 10
    int numRecords = PositiveInt("\n Enter the number of records to Add: ");
    numRecords = min(numRecords, maxRecords);


    for (int i = 0; i < numRecords; ++i) {
        Record record;
        cout << "\n Enter Student name for record " << i + 1 << ": ";
        getline(cin, record.StudentName);
        record.StudentName = capitalizeWord(record.StudentName);

        cout << " Enter Student Roll (1-100) for record " << i + 1 << ": ";

        // Check if the roll number already exists
        if (ValidRollNum(record.RollNum))
        {
            if (RollNumExists(record.RollNum)) {
            cout << "Roll number already exists. Please enter a different roll number." << endl;
            --i;
            }
            else {
                insertRecord(outputFile, record);
                cout << "Student record successfully added." << endl;
                 // Valid and unique roll number, exit the loop
            }
        }
        else {
            cout << "Invalid roll number. Roll number should be between 1 and 100." << endl;
            --i; // Decrement i to re-enter the current record
        }
    }

    outputFile.close();
    return 0;
}

bool removeStudent() {
    int rollToDelete;

    do {
        cout << "\n Enter the roll number of the student to delete (1-100): ";
        if (ValidRollNum(rollToDelete)) {
            if (!RollNumExists(rollToDelete)) {
                cout << "Student record with Roll Number " << rollToDelete << " does not exist. Please try again." << endl;
            }
            else {
                break;
            }
        }
        else {
            if(rollToDelete / 1)
                cout << "Roll number should be between 1 and 100. Please try again." << endl;
            else
                cout << "Invalid input. Please enter a valid number." << endl;
        }
    } while (true);

    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file for reading." << endl;
        return false;
    }

    ofstream tempFile("temp_records.txt");

    if (!tempFile) {
        cerr << "Error creating temporary file." << endl;
        inputFile.close();
        return false;
    }

    bool found = false;
    string line;

    while (getline(inputFile, line)) {
        Record record;
        size_t commaPos = line.find(",");
        if (commaPos != string::npos) {
            record.StudentName = line.substr(0, commaPos);
            record.RollNum = stoi(line.substr(commaPos + 1));
            if (record.RollNum == rollToDelete) {
                found = true;
            }
            else {
                insertRecord(tempFile, record);
            }
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        if (remove(filename.c_str()) != 0) {
            cerr << "Error: Unable to remove the original file." << endl;
            return false; // Handle the error appropriately
        }
        if (rename("temp_records.txt", filename.c_str()) != 0) {
            cerr << "Error: Unable to rename the temporary file." << endl;
            return false; // Handle the error appropriately
        }
        cout << "Student record with Roll Number " << rollToDelete << " deleted." << endl;
        return true;
    }

    else {
        cout << "Student record with Roll Number " << rollToDelete << " not found." << endl;
        if (remove("temp_records.txt") != 0) {
            cerr << "Error: Unable to remove the temporary file." << endl;
            // Handle the error appropriately
        }
        return false;
    }

}

void searchRecords(const vector<Record> &records, const string& query) {
    cout << "\n Search results for '" << query << "':\n";
    bool found = false;
    for (const Record& record : records) {
        if (record.StudentName.find(query) != string::npos) {
            cout << "Name: " << record.StudentName << " \t Rollnum: " << record.RollNum << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matching records found." << endl;
    }
}

void showStudents() {
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    int option;
    bool exitLoop = false;

    while (!exitLoop) {

        cout << "\nChoose an option: " << endl;
        cout << "1. Show entire student list" << endl;
        cout << "2. Search for a student by name" << endl;
        cout << "3. Go Back" << endl;
        option = ValidIntInput(" Enter option number: ", 1, 3);

        switch (option) {
        case 1: {
            string line;
            int recordCount = 0;

            inputFile.clear(); 
            inputFile.seekg(0);

            cout << "\nList of Student Records:\n";

            while (getline(inputFile, line)) {
                Record record;
                stringstream ss(line);
                getline(ss, record.StudentName, ',');
                ss >> record.RollNum;
                cout << "Record " << recordCount + 1 << ": " << record.StudentName << " \t Roll: " << record.RollNum << "\n";
                recordCount++;
            }

            if (recordCount == 0) {
                cout << "No records found.\n";
            }
            break;
        }
        case 2: {
            vector<Record> records;
            string line;

            inputFile.clear(); 
            inputFile.seekg(0);

            while (getline(inputFile, line)) {
                Record record;
                stringstream ss(line);
                getline(ss, record.StudentName, ',');
                ss >> record.RollNum;
                records.push_back(record);
            }

            if (records.empty()) {
                cout << "No records found in the file." << endl;
            }
            else {
                cin.ignore(); // Consume the newline character left in the input buffer after entering the option.
                cout << "Enter a name to search: ";
                string query;
                getline(cin, query);
                query = capitalizeWord(query);
                searchRecords(records, query);
            }
            break;
        }
        case 3:
            exitLoop = true;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }

    inputFile.close();
}


