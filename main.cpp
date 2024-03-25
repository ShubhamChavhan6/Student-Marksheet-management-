#include "portal.h"
#include "password-color.h"

class Myclass {
public:
	void welcome() {
        printColorfulText("Y.C J.r College", COLOR_BLUE);
        printColorfulText("Class 11th (Computer Science)", COLOR_YELLOW);
	}
};

int main()
{
	Myclass objclass;

	objclass.welcome();

    User teacher("teacher_pass", "Teacher");
    User student("student_pass", "Student");
    User clerk("clerk_pass", "Clerk");

    User* users[] = { &teacher, &student, &clerk }; // Array of User pointers

    string inputPass;
    inputPassword(inputPass);

    bool authenticated =false;
    // Loop through the users and check the password
    for (User* user : users) 
    {
        if (user->authenticate(inputPass)) {
            user->accessAdminPortal();
            authenticated = true;
            break; // Exit the loop after successful authentication
        }
    }

    if (!authenticated) {
        cout << "\n Authentication failed. Access denied." << endl;
    }

    return 0;
}