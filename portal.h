#pragma once
#include "operation.h"
#include "Marksheet.h"
#include "password-color.h"

class Student {
public:
    std::string name;
    Student(const std::string& n) : name(n) {}

    std::string getName() const {
        return name;
    }
};

class User {
public:
    std::string password;
    std::string role;

    User(const std::string& pass, const std::string& r) : password(pass), role(r) {}

    bool authenticate(const std::string& inputPass) const {
        return password == inputPass;
    }

    void accessAdminPortal() {
        if (role == "Teacher") {
            teacherAdminPortal();
        }
        else if (role == "Student") {
            studentAdminPortal();
        }
        else if (role == "Clerk") {
            staffAdminPortal();
        }
        else {
            std::cout << "Unknown role. Access to admin portal denied." << std::endl;
        }
    }

    void teacherAdminPortal() {
        int option;
        do {
            printColorfulText(" Logged in to Teacher potral\n", COLOR_GREEN);
            //std::cout << " Logged in to Teacher potral\n" << std::endl;
            std::cout << "\nChoose an option: " << std::endl;
            printColorfulText("1. Manage Students", COLOR_LIGHT_BLUE);
            printColorfulText("2. Manage Marksheet", COLOR_LIGHT_BLUE);
            printColorfulText("3. Exit\n", COLOR_RED);
            option = ValidIntInput(" Enter option number: ", 1, 3);

            switch (option) {
            case 1:
                Students();
                break;
            case 2:
                Marksheet();
                break;
            case 3:
                std::cout << "Exiting Teacher portal..." << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        } while (option != 3);
    }

    void studentAdminPortal() {
        int option;
        do {
            std::cout << "\nChoose an option: " << std::endl;
            printColorfulText("1. Show Students", COLOR_CYAN);
            printColorfulText("2. Show Marksheet", COLOR_CYAN);
            printColorfulText("3. Exit\n", COLOR_RED);
            option = ValidIntInput(" Enter option number: ", 1, 3);

            switch (option) {
            case 1:
                showStudents();
                break;
            case 2:
                showMarksheet();
                break;
            case 3:
                std::cout << "Exiting Student portal..." << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        } while (option != 3);
    }

    void staffAdminPortal() {
        int option;
        do {
            std::cout << "\nChoose an option: " << std::endl;
            printColorfulText("1. Add Students", COLOR_GREEN);
            printColorfulText("2. Show Students", COLOR_CYAN);
            printColorfulText("3. Create Marksheet", COLOR_GREEN);
            printColorfulText("4. Show Marksheet", COLOR_CYAN);
            printColorfulText("5. Exit", COLOR_RED);
            option = ValidIntInput(" Enter option number: ", 1, 5);

            switch (option) {
            case 1:
                addStudents();
                break;
            case 2:
                showStudents();
                break;
            case 3:
                createMarkSheet();
                break;
            case 4:
                showMarksheet();
                break;
            case 5:
                std::cout << "Exiting clerk portal..." << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        } while (option != 5);
    }

    void Students() {
        int option;
        do {
            std::cout << "\nChoose an option: " << std::endl;
            printColorfulText("1. Add Students", COLOR_GREEN);
            printColorfulText("2. Remove Students", COLOR_MAGENTA);
            printColorfulText("3. Show Students", COLOR_CYAN);
            printColorfulText("4. Go back", COLOR_GRAY);
            option = ValidIntInput(" Enter option number: ", 1, 4);

            switch (option) {
            case 1:
                addStudents();
                break;
            case 2:
                removeStudent();
                break;
            case 3:
                showStudents();
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        } while (option != 4);

    }
    void Marksheet() {
        int option;
        do {
            std::cout << "\nChoose an option: " << std::endl;
            printColorfulText("1. Create Marksheet", COLOR_GREEN);
            printColorfulText("2. Update Marksheet", COLOR_YELLOW);
            printColorfulText("3. Delete Marksheet", COLOR_MAGENTA);
            printColorfulText("4. Show Marksheet", COLOR_CYAN);
            printColorfulText("5. Go back", COLOR_GRAY);
            option = ValidIntInput(" Enter option number: ", 1, 5);

            switch (option) {
            case 1:
                createMarkSheet();
                break;
            case 2:
                updateMarksheet();
                break;
            case 3:
                DeleteMarkSheet();
                break;
            case 4:
                showMarksheet();
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        } while (option != 5);
    }

    void showMarksheet() {
        int choice;
        while (true) {
            std::cout << "\nOptions:\n";
            std::cout << "1. Show All Records\n";
            std::cout << "2. Search for a Record\n";
            printColorfulText("3. Go Back", COLOR_GRAY);
            choice = ValidIntInput(" Enter option number: ", 1, 3);

            switch (choice) {
            case 1:
                showAllRecords(); // Display all records
                break;
            case 2:
                searchMarkSheet(); // Search for a specific record
                break;
            case 3:
                return; // Exit the function
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    }

};