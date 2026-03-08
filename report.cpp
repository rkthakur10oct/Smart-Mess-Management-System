// report.cpp
#include "report.h"
#include "ui.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Attendance Report Viewer
void generateAttendanceReport() {
    printHeader("Attendance Report");

    string file;
    int choice;
    cout << "1. Student Attendance\n";
    cout << "2. Staff Attendance\n";
    cout << "Choose option: ";
    cin >> choice;

    if (choice == 1) file = "data/attendance_student.txt";
    else if (choice == 2) file = "data/attendance_staff.txt";
    else {
        cout << "Invalid choice!\n";
        pauseAndContinue();
        return;
    }

    ifstream fin(file);
    string line;
    int count = 0;

    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }

    if (count == 0) cout << "No attendance records found.\n";
    fin.close();
    pauseAndContinue();
}

// Finance Report Viewer
void generateFinanceReport() {
    printHeader("Finance Report");

    ifstream fin("data/finance.txt");
    string line;
    float income = 0, expense = 0;
    int count = 0;

    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";

        stringstream ss(line);
        string type, date, desc, amtStr;
        getline(ss, type, '|');
        getline(ss, date, '|');
        getline(ss, desc, '|');
        getline(ss, amtStr, '|');
        float amt = stof(amtStr);

        if (type == "Income") income += amt;
        else if (type == "Expense") expense += amt;
    }

    float profit = income - expense;
    cout << fixed << setprecision(2);
    cout << "\nSummary:\n";
    cout << "Total Income : Rs." << income << "\n";
    cout << "Total Expense: Rs." << expense << "\n";
    cout << (profit >= 0 ? "Net Profit   : Rs." : "Net Loss     : ₹") << abs(profit) << "\n";

    fin.close();
    pauseAndContinue();
}

// Feedback Report Viewer
void generateFeedbackReport() {
    printHeader("Feedback Report");

    ifstream fin("data/feedback.txt");
    string line;
    int count = 0;

    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }

    if (count == 0) cout << "No feedback available.\n";
    fin.close();
    pauseAndContinue();
}

// Main Report Panel
void reportPanel() {
    int choice;
    do {
        printHeader("Reports Panel");

        cout << "1. Attendance Report\n";
        cout << "2. Finance Report\n";
        cout << "3. Feedback Report\n";
        cout << "4. Back to Admin Dashboard\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1: generateAttendanceReport(); break;
            case 2: generateFinanceReport(); break;
            case 3: generateFeedbackReport(); break;
            case 4: return;
            default: cout << "Invalid option!\n"; pauseAndContinue();
        }
    } while (true);
}
