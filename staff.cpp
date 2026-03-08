// staff.cpp - Staff dashboard module for Smart Mess Management System
#include "staff.h"
#include "ui.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// View profile info of staff
void viewStaffProfile(const string& username) {
    printHeader("Staff Profile");
    cout << "Welcome: " << username << endl;
    ifstream fin("data/staff.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);

        if (fields.size() >= 8 && fields[2] == username) {
            found = true;
            cout << "ID        : " << fields[0] << "\n";
            cout << "Name      : " << fields[1] << "\n";
            cout << "Gender    : " << fields[4] << "\n";
            cout << "Role      : " << fields[5] << "\n";
            cout << "Salary    : Rs." << fields[6] << "\n";
            cout << "Joined On : " << fields[7] << "\n";
            break;
        }
    }
    if (!found) cout << "Staff not found.\n";
    fin.close();
    pauseAndContinue();
}

// View staff attendance records
void viewStaffAttendance(const string& username) {
    printHeader("Attendance History");
    ifstream fin("data/attendance_staff.txt");
    string line;
    int count = 0;

    while (getline(fin, line)) {
        if (line.find(username) != string::npos) {
            cout << ++count << ". " << line << "\n";
        }
    }
    if (count == 0) cout << "No attendance records found.\n";
    fin.close();
    pauseAndContinue();
}

// View salary payment status (Paid/Unpaid)
void viewSalaryStatus(const string& username) {
    printHeader("Salary Status");
    ifstream fin("data/staff_salaries.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        string uname, status;
        getline(ss, uname, '|');
        getline(ss, status, '|');
        if (uname == username) {
            cout << "Salary Status: " << status << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "No salary status available.\n";
    fin.close();
    pauseAndContinue();
}

// Staff submits feedback
void submitStaffFeedback(const string& username) {
    printHeader("Submit Feedback");
    string feedback;
    cin.ignore();
    cout << "Write your feedback:\n> ";
    getline(cin, feedback);

    ofstream fout("data/feedback.txt", ios::app);
    fout << "STA:" << username << "|" << feedback << "|Pending\n";
    fout.close();

    cout << "Feedback submitted.\n";
    pauseAndContinue();
}

// Staff resets their own password
void resetStaffPassword(const string& username) {
    printHeader("Reset Password");
    string newPass;

    while (true) {
        cout << "Enter new password (min 8 chars): ";
        newPass = getMaskedPassword();
        if (newPass.length() < 8) {
            cout << "Password must be at least 8 characters. Try again.\n";
            continue;
        }
        break;
    }

    ifstream fin("data/staff.txt");
    ofstream fout("data/temp.txt");
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);

        if (fields[2] == username) fields[3] = newPass;

        for (size_t i = 0; i < fields.size(); ++i) {
            fout << fields[i];
            if (i != fields.size() - 1) fout << "|";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    remove("data/staff.txt");
    rename("data/temp.txt", "data/staff.txt");

    cout << "Password updated.\n";
    pauseAndContinue();
}

// Staff Dashboard
void staffDashboard(const string& username) {
    int choice;
    do {
        printHeader("Staff Dashboard");
        cout << "1. View Profile\n";
        cout << "2. View Attendance\n";
        cout << "3. View Salary Status\n";
        cout << "4. Submit Feedback\n";
        cout << "5. Reset Password\n";
        cout << "6. View My Feedback Status\n";
        cout << "7. Manage My Feedback\n";
        cout << "8. Logout\n";
        cout << "\nSelect option: ";
        cin >> choice;

        switch (choice) {
            case 1: viewStaffProfile(username); break;
            case 2: viewStaffAttendance(username); break;
            case 3: viewSalaryStatus(username); break;
            case 4: submitStaffFeedback(username); break;
            case 5: resetStaffPassword(username); break;
            case 6: viewOwnFeedback(username, "STAFF"); break;
            case 7: manageOwnFeedback(username, "STAFF"); break;
            case 8: return;
            default: cout << "Invalid option!\n"; pauseAndContinue();
        }
    } while (true);
}