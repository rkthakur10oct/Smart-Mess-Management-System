// auth.cpp - Full authentication system with admin-controlled registration
#include "auth.h"
#include "admin.h"
#include "student.h"
#include "staff.h"
#include "guest.h"
#include "ui.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

// ------------------ Admin Registration (Only Once) ------------------
void adminRegister() {
    printHeader("Admin Registration");

    // Ensure data directory exists
if (!fs::exists("data")) {
    fs::create_directory("data");
}
    // Check if admin is already registered
    ifstream check("data/admin.dat");
    string temp;
    if (getline(check, temp)) {
        cout << "Admin already exists.\n"; pauseAndContinue(); return;
    }
    check.close();

    string uname, pass, name, gender, dob, email, phone1, phone2, address, fname, mname, secQ, secA;

    name = getValidatedInput("Full Name             : ", "");
    while (true) {
        uname = getValidatedInput("Username              : ", "");
        if (!isUsernameUnique(uname)) {
            cout << "Username exists!\n"; continue;
        }
        break;
    }
    while (true) {
        cout << "Password              : ";
        pass = getMaskedPassword();
        if (pass.length() < 8) {
            cout << "Password must be at least 8 characters.\n"; continue;
        }
        break;
    }
    gender = getValidatedInput("Gender (M/F)          : ", "");
    dob = getValidatedInput("DOB (DD-MM-YYYY)      : ", "date");
    email = getValidatedInput("Email Address         : ", "email");
    phone1 = getValidatedInput("Primary Phone         : ", "phone");
    cout << "Alternate Phone (Opt) : ";
    getline(cin, phone2);  // Optional field; user can leave it blank
    fname = getValidatedInput("Father's Name         : ", "");
    mname = getValidatedInput("Mother's Name         : ", "");
    address = getValidatedInput("Address               : ", "");
    secQ = getValidatedInput("Security Question     : ", "");
    secA = getValidatedInput("Answer                : ", "");

    ofstream fout("data/admin.dat");
    fout << uname << "|" << pass << "|" << name << "|" << gender << "|" << dob << "|" << email << "|"
         << phone1 << "|" << phone2 << "|" << fname << "|" << mname << "|" << address << "|" << secQ << "|" << secA << "\n";
    fout.close();
    cout << "Admin registered successfully.\n";
    pauseAndContinue();
}

// ------------------ Admin Login ------------------
void adminLogin() {
    while (true) {
        clearScreen();
        printHeader("Admin Login");

        ifstream fin("data/admin.dat");
        string line;

        if (!getline(fin, line)) {
            cout << "Admin is not registered yet. Please run 'Register Admin' option first.\n";
            pauseAndContinue();
            return;
        }

        string uname, pass;
        cout << "Username: ";
        cin >> uname;
        cout << "Password: ";
        pass = getMaskedPassword();

        stringstream ss(line);
        vector<string> flds;
        string temp;
        while (getline(ss, temp, '|')) flds.push_back(temp);

        if (flds.size() >= 2 && trim(flds[0]) == trim(uname) && trim(flds[1]) == trim(pass)) {
            cout << "Login successful.\n";
            pauseAndContinue();
            adminDashboard();
            return;
        } else {
            cout << "Invalid admin credentials.\n";
            char choice;
            cout << "\nDo you want to try again? (Y/N): ";
            cin >> choice;
            if (tolower(choice) != 'y') {
                cout << "Returning to main menu...\n";
                pauseAndContinue();
                return;
            }
        }
    }
}

// ------------------ Student Login ------------------
void studentLogin() {
    printHeader("Student Login");
    string uname, pass;
    cout << "Username: "; cin >> uname;
    cout << "Password: "; pass = getMaskedPassword();
    ifstream fin("data/students.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> flds;
        string temp;
        while (getline(ss, temp, '|')) flds.push_back(temp);
        if (flds.size() > 3 && flds[2] == uname && flds[3] == pass) {
            studentDashboard(uname); return;
        }
    }
    cout << "Invalid student credentials.\n"; pauseAndContinue();
}

// ------------------ Staff Login ------------------
void staffLogin() {
    printHeader("Staff Login");
    string uname, pass;
    cout << "Username: "; cin >> uname;
    cout << "Password: "; pass = getMaskedPassword();
    ifstream fin("data/staff.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> flds;
        string temp;
        while (getline(ss, temp, '|')) flds.push_back(temp);
        if (flds.size() > 3 && flds[2] == uname && flds[3] == pass) {
            staffDashboard(uname); return;
        }
    }
    cout << "Invalid staff credentials.\n"; pauseAndContinue();
}

// ------------------ Guest Register ------------------
void guestRegister() {
    printHeader("Guest Registration");

    // Ensure data directory exists
if (!fs::exists("data")) {
    fs::create_directory("data");
}
    // Check if guest is already registered
    string name, uname, pass, gender, email, phone, meal, secQ, secA;
    name = getValidatedInput("Name              : ", "");
    while (true) {
        uname = getValidatedInput("Username          : ", "");
        if (!isUsernameUnique(uname)) {
            cout << "Username exists!\n"; continue;
        }
        break;
    }
    while (true) {
        cout << "Password          : ";
        pass = getMaskedPassword();
        if (pass.length() < 8) {
            cout << "Password must be at least 8 characters.\n"; continue;
        }
        break;
    }
    gender = getValidatedInput("Gender (M/F)      : ", "");
    email = getValidatedInput("Email Address     : ", "email");
    phone = getValidatedInput("Phone Number      : ", "phone");
    meal = getValidatedInput("Meal Preference   : ", "");
    secQ = getValidatedInput("Security Question : ", "");
    secA = getValidatedInput("Answer            : ", "");

    ofstream fout("data/guests.txt", ios::app);
    fout << name << "|" << uname << "|" << pass << "|" << gender << "|" << email << "|"
         << phone << "|" << meal << "|" << secQ << "|" << secA << "\n";
    fout.close();

    logAudit("Guest self-registered: " + uname);  // Record in audit
    cout << "Guest registered successfully.\n";
    pauseAndContinue();
}

// ------------------ Guest Login ------------------
void guestLogin() {
    printHeader("Guest Login");
    string uname, pass;
    cout << "Username: "; cin >> uname;
    cout << "Password: "; pass = getMaskedPassword();
    ifstream fin("data/guests.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> flds;
        string temp;
        while (getline(ss, temp, '|')) flds.push_back(temp);
        if (flds.size() > 2 && flds[1] == uname && flds[2] == pass) {
            guestMenu(uname); return;
        }
    }
    cout << "Invalid guest credentials.\n"; pauseAndContinue();
}

// ------------------ Recover Password ------------------
void recoverPassword(const string& role) {
    printHeader("Recover Password");
    string file; int unameIndex = 2;
    if (role == "admin") { file = "data/admin.dat"; unameIndex = 0; }
    else if (role == "student") file = "data/students.txt";
    else if (role == "staff") file = "data/staff.txt";
    else if (role == "guest") file = "data/guests.txt";
    else return;

    string uname;
    cout << "Enter your username: "; cin >> uname;
    if (verifySecretQA(file, unameIndex, uname)) {
        cout << "Enter new password: ";
        string newPass = getMaskedPassword();
        updatePasswordInFile(file, unameIndex, uname, newPass);
        cout << "Password updated.\n";
    } else cout << "Recovery failed.\n";
    pauseAndContinue();
}

// ------------------ Guest Access ------------------
void guestAccess() {
    printHeader("Guest Access");
    int choice;
    cout << "1. Guest Login\n";
    cout << "2. Guest Register\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: guestLogin(); break;
        case 2: guestRegister(); break;
        case 3: return;
        default: cout << "Invalid choice.\n"; pauseAndContinue();
    }
}

// ------------------ Recover Username ------------------
void recoverUsername(const string& role) {
    printHeader("Recover Username");
    string file; int emailIndex = 5, unameIndex = 0;
    if (role == "admin") { file = "data/admin.dat"; emailIndex = 5; unameIndex = 0; }
    else if (role == "student") { file = "data/students.txt"; emailIndex = 11; unameIndex = 2; }
    else if (role == "staff") { file = "data/staff.txt"; emailIndex = 11; unameIndex = 2; }
    else if (role == "guest") { file = "data/guests.txt"; emailIndex = 4; unameIndex = 1; }
    else return;

    string input;
    cout << "Enter your registered email or phone: ";
    cin.ignore(); getline(cin, input);

    ifstream fin(file);
    string line;
    bool found = false;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> flds;
        string temp;
        while (getline(ss, temp, '|')) flds.push_back(temp);
        if ((emailIndex < flds.size()) && (flds[emailIndex] == input || flds[emailIndex - 1] == input)) {
            cout << "Your username is: " << flds[unameIndex] << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "No matching record found.\n";
    pauseAndContinue();
}
