// student.cpp - Student dashboard module for Smart Mess Management System
#include "student.h"
#include "ui.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// View student profile
void viewStudentProfile(const string& username) {
    printHeader("Student Profile");
    cout << "Welcome: " << username << endl;
    ifstream fin("data/students.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);

        if (fields.size() >= 9 && fields[2] == username) {
            found = true;
            cout << "ID        : " << fields[0] << "\n";
            cout << "Name      : " << fields[1] << "\n";
            cout << "Gender    : " << fields[4] << "\n";
            cout << "Branch    : " << fields[5] << "\n";
            cout << "Year      : " << fields[6] << "\n";
            cout << "Dues      : ₹" << fields[7] << "\n";
            cout << "Joined On : " << fields[8] << "\n";
            break;
        }
    }
    if (!found) cout << "Student not found.\n";
    fin.close();
    pauseAndContinue();
}

// View student attendance
void viewAttendance(const string& username) {
    printHeader("Attendance");
    ifstream fin("data/attendance_student.txt");
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

// Submit feedback to admin
void submitFeedback(const string& username) {
    printHeader("Submit Feedback");
    string feedback;
    cin.ignore();
    cout << "Write your feedback:\n> ";
    getline(cin, feedback);

    ofstream fout("data/feedback.txt", ios::app);
    fout << "STU:" << username << "|" << feedback << "|Pending\n";
    fout.close();

    cout << "Feedback submitted.\n";
    pauseAndContinue();
}

// Reset student password
void resetStudentPassword(const string& username) {
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

    ifstream fin("data/students.txt");
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
    remove("data/students.txt");
    rename("data/temp.txt", "data/students.txt");

    cout << "Password updated.\n";
    pauseAndContinue();
}

// Pre-book meals for the week
void preBookMeals(const string& username) {
    printHeader("Meal Pre-Booking");

    ifstream menu("data/weekly_menu.txt");
    vector<string> days, slots, meals;
    string line;

    while (getline(menu, line)) {
        string day, slot, meal;
        stringstream ss(line);
        getline(ss, day, '|');
        getline(ss, slot, '|');
        getline(ss, meal);
        days.push_back(day);
        slots.push_back(slot);
        meals.push_back(meal);
    }
    menu.close();

    ofstream fout("data/meal_bookings.txt", ios::app);

    for (int i = 0; i < 7; ++i) {
        string date = getFutureDate(i);
        bool isHoliday = false;
        ifstream hfile("data/holidays.txt");
        string hline;
        while (getline(hfile, hline)) {
            if (hline.find(date) != string::npos) {
                isHoliday = true;
                break;
            }
        }
        hfile.close();

        if (isHoliday) {
            cout << "\n" << date << " is a holiday. Skipping meal booking.\n";
            continue;
        }

        string day = days[i % days.size()];
        string slot = slots[i % slots.size()];
        string meal = meals[i % meals.size()];
        string choice;

        cout << "\n" << day << " - " << slot << " (" << date << "): " << meal << "\n";
        cout << "Do you want this meal? (Yes/No): ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        fout << username << "|" << date << "|" << slot << "|" << (choice == "yes" ? "Yes" : "No") << "\n";
    }

    fout.close();
    cout << "\nMeals pre-booked successfully.\n";
    pauseAndContinue();
}

// Student Dashboard
void studentDashboard(const string& username) {
    int choice;
    do {
        printHeader("Student Dashboard");

        cout << "1. View Profile\n";
        cout << "2. View Attendance\n";
        cout << "3. Submit Feedback\n";
        cout << "4. Reset Password\n";
        cout << "5. Pre-Book Meals\n";
        cout << "6. View My Feedback Status\n";
        cout << "7. Manage My Feedback\n";
        cout << "8. Go Back\n";
        cout << "9. Go Forward\n";
        cout << "10. Logout\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewStudentProfile(username); break;
            case 2: viewAttendance(username); break;
            case 3: submitFeedback(username); break;
            case 4: resetStudentPassword(username); break;
            case 5: preBookMeals(username); break;
            case 6: viewOwnFeedback(username, "STUDENT"); break;
            case 7: manageOwnFeedback(username, "STUDENT"); break;
            case 8:
                if (canGoBack()) {
                    string prev = popBack();
                    cout << "Back to: " << prev << "\n";
                } else {
                    cout << "No previous screen available.\n";
                }
                pauseAndContinue();
                break;

            case 9:
                if (canGoForward()) {
                    string next = popForward();
                    cout << "Forward to: " << next << "\n";
                } else {
                    cout << "No forward screen available.\n";
                }
                pauseAndContinue();
                break;
            case 10: return;
            default: cout << "Invalid choice!\n"; pauseAndContinue();
        }
    } while (true);
}
