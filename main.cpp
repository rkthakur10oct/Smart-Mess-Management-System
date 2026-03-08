// main.cpp
#include <iostream>
#include "modules/auth.h"
#include "modules/ui.h"

using namespace std;

void displayMainMenu() {
    printHeader("Smart Mess Management System");

    cout << "0. Register Admin (First-time only)\n";
    cout << "1. Admin Login\n";
    cout << "2. Student Login\n";
    cout << "3. Staff Login\n";
    cout << "4. Guest Panel\n";
    cout << "5. Recover Password\n";
    cout << "6. Recover Username\n";
    cout << "7. Exit\n";
    cout << "\nEnter your choice: ";
}

void recoverPasswordMenu() {
    printHeader("Password Recovery");
    int choice;
    cout << "1. Admin\n";
    cout << "2. Student\n";
    cout << "3. Staff\n";
    cout << "4. Guest\n";
    cout << "5. Back\n";
    cout << "\nEnter role to recover password for: ";
    cin >> choice;

    switch (choice) {
        case 1: recoverPassword("admin"); break;
        case 2: recoverPassword("student"); break;
        case 3: recoverPassword("staff"); break;
        case 4: recoverPassword("guest"); break;
        case 5: return;
        default: cout << "Invalid choice.\n"; pauseAndContinue();
    }
}

void recoverUsernameMenu() {
    printHeader("Username Recovery");
    int choice;
    cout << "1. Admin\n";
    cout << "2. Student\n";
    cout << "3. Staff\n";
    cout << "4. Guest\n";
    cout << "5. Back\n";
    cout << "\nEnter role to recover username for: ";
    cin >> choice;

    switch (choice) {
        case 1: recoverUsername("admin"); break;
        case 2: recoverUsername("student"); break;
        case 3: recoverUsername("staff"); break;
        case 4: recoverUsername("guest"); break;
        case 5: return;
        default: cout << "Invalid choice.\n"; pauseAndContinue();
    }
}

int main() {
    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 0: adminRegister(); break;
            case 1: adminLogin(); break;
            case 2: studentLogin(); break;
            case 3: staffLogin(); break;
            case 4: guestAccess(); break;
            case 5: recoverPasswordMenu(); break;
            case 6: recoverUsernameMenu(); break;
            case 7:
                cout << "\nExiting... Thank you for using Smart Mess Management System!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseAndContinue();
        }
    }
    return 0;
}
