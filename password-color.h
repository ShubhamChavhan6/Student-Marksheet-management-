#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

void inputPassword(string& password)
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    // Get the current input mode
    GetConsoleMode(hStdin, &mode);

    // Disable input echo (password mode)
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    cout << "\n Enter your password: ";
    char ch;
    while (true)
    {
        ch = _getch(); // Read a character without echoing it

        if (ch == 13) // Check for Enter key press (ASCII 13)
            break;
        else if (ch == 8 && !password.empty())
        {                        // Handle backspace (ASCII 8)
            cout << "\b \b";     // Move cursor back, print space, move cursor back again
            password.pop_back(); // Remove the last character from the password
        }
        else
        {
            cout << (ch == ' ' ? ' ' : '*'); // Print space or '*' for each character entered
            password.push_back(ch);
        }
    }
    cout << endl; // Print a newline after the password

    // Restore the original input mode
    SetConsoleMode(hStdin, mode);
}


    const int COLOR_BLACK = 0;
    const int COLOR_BLUE = 1;
    const int COLOR_GREEN = 2;
    const int COLOR_CYAN = 3;
    const int COLOR_RED = 4;
    const int COLOR_MAGENTA = 5;
    const int COLOR_YELLOW = 6;
    const int COLOR_WHITE = 7;
    const int COLOR_GRAY = 8;
    const int COLOR_LIGHT_BLUE = 9;


void printColorfulText(const std::string& text, int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the console text attribute to display text in the specified color
    SetConsoleTextAttribute(hConsole, textColor);

    // Print the text
    std::cout << text << std::endl;

    // Reset the console text attribute to default (usually white on black)
    SetConsoleTextAttribute(hConsole, COLOR_WHITE); // You can change this to your default color
}