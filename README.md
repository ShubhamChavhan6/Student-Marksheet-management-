# Student Marksheet Management System

A simple C++ based console application for managing student records and marksheets, designed for academic institutions. This project allows teachers, clerks, and students to securely access and manage student data such as personal details and subject marks. The system supports adding, searching, updating, and deleting student records and marksheets.

## Features

- **User Authentication:** Role-based access for Teacher, Clerk, and Student.
- **Student Record Management:** Add, search, display, and delete student personal records.
- **Marksheet Management:** Create, update, search, and delete marksheets for students.
- **Input Validation:** Ensures correctness of entered data (e.g., roll numbers, subject marks).
- **Console UI:** Simple, menu-driven interface with colored text for clarity.

## Technologies Used

- **C++** (Standard Library)
- Windows console (for colorized output)
- File I/O for persistent storage (`.csv` files)

## Getting Started

### Prerequisites

- **Compiler:** Any C++ compiler (tested with MSVC/g++)
- **Platform:** Windows (due to use of Windows.h for colored output)

### Setup & Compilation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/akshad-exe/Student-Marksheet-management-.git
   cd Student-Marksheet-management-
   ```
2. **Compile the code:**  
   (Ensure all `.cpp` and `.h` files are in the same directory)
   ```sh
   g++ main.cpp -o marksheet.exe
   ```
   Or use your preferred C++ build method.

3. **Run the application:**
   ```sh
   ./marksheet.exe
   ```

## Usage

1. On launch, you will see a welcome message for "Y.C J.r College, Class 11th (Computer Science)."
2. Enter the password for your role (Teacher/Student/Clerk) to access the respective portal.
3. Perform actions such as adding students, creating marksheets, searching, updating, or deleting records.

### Example Operations

- **Add Students:** Enter names and unique roll numbers (1-100).
- **Create Marksheet:** Assign marks for English, Physics, Chemistry, Math, Computer.
- **Update Marksheet:** Modify existing marks for a student.
- **Search:** Look up students or marksheets by name or roll number.
- **Delete:** Remove records or marksheets as needed.

## File Structure

- `main.cpp` — Entry point, handles authentication and launches portals.
- `portal.h` — User roles and portal logic.
- `operation.h` — Student record CRUD operations.
- `Marksheet.h` — Marksheet CRUD operations and calculations.
- `input_valid.h`, `password-color.h` — Input validation and colored output (Windows only).

## Notes

- Data is stored in CSV files for persistence.
- Only roll numbers between 1 and 100 are accepted.
- The application is console-based and currently supports Windows due to color output dependencies.

## License

MIT License

---

*Created by akshad-exe*
