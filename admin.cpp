// admin.cpp - Full implementation for admin panel with student/staff/guest registration
#include "admin.h"
#include "ui.h"
#include "utils.h"
#include "enquiry.h"
#include "feedback.h"
#include "finance.h"
#include "inventory.h"
#include "report.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

// ------------------ Register Student ------------------
void registerStudent() {
    printHeader("Register Student");
    string id, name, uname, pass, gender, branch, year, dues, doj, fname, mname, email, phone1, phone2, address, secQ, secA;

    id = getValidatedInput("Student ID            : ", "");
    name = getValidatedInput("Full Name             : ", "");

    while (true) {
        uname = getValidatedInput("Username              : ", "");
        if (uname == "cancel") return;
        if (!isUsernameUnique(uname)) {
            cout << "Username already exists!\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Password              : ";
        pass = getMaskedPassword();
        if (pass.length() < 8) {
            cout << "Password must be at least 8 characters.\n";
            continue;
        }
        break;
    }

    gender = getValidatedInput("Gender (M/F)          : ", "");
    branch = getValidatedInput("Branch                : ", "");
    year = getValidatedInput("Year                  : ", "");
    dues = getValidatedInput("Initial Dues Rs.        : ", "");
    doj = getValidatedInput("Date of Joining       : ", "date");
    fname = getValidatedInput("Father's Name         : ", "");
    mname = getValidatedInput("Mother's Name         : ", "");
    email = getValidatedInput("Email Address         : ", "email");
    phone1 = getValidatedInput("Primary Phone         : ", "phone");
    cout << "Alternate Phone (Opt) : ";
    getline(cin, phone2);  // Optional field; user can leave it blank
    address = getValidatedInput("Address               : ", "");
    secQ = getValidatedInput("Security Question     : ", "");
    secA = getValidatedInput("Answer                : ", "");

    ofstream fout("data/students.txt", ios::app);
    fout << id << "|" << name << "|" << uname << "|" << pass << "|" << gender << "|" << branch << "|" << year << "|" << dues << "|"
         << doj << "|" << fname << "|" << mname << "|" << email << "|" << phone1 << "|" << phone2 << "|" << address << "|"
         << secQ << "|" << secA << "\n";
    fout.close();
    
    logAudit("Admin registered a new student: " + uname);
    cout << "Student registered successfully.\n";
    pauseAndContinue();
}

// ------------------ Register Staff ------------------
void registerStaff() {
    printHeader("Register Staff");
    string id, name, uname, pass, gender, role, salary, doj, fname, mname, email, phone1, phone2, address, secQ, secA;

    id = getValidatedInput("Staff ID              : ", "");
    name = getValidatedInput("Full Name             : ", "");

    while (true) {
        uname = getValidatedInput("Username              : ", "");
        if (uname == "cancel") return;
        if (!isUsernameUnique(uname)) {
            cout << "Username already exists!\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Password              : ";
        pass = getMaskedPassword();
        if (pass.length() < 8) {
            cout << "Password must be at least 8 characters.\n";
            continue;
        }
        break;
    }

    gender = getValidatedInput("Gender (M/F)          : ", "");
    role = getValidatedInput("Designation/Role      : ", "");
    salary = getValidatedInput("Salary Rs.              : ", "");
    doj = getValidatedInput("Date of Joining       : ", "date");
    fname = getValidatedInput("Father's Name         : ", "");
    mname = getValidatedInput("Mother's Name         : ", "");
    email = getValidatedInput("Email Address         : ", "email");
    phone1 = getValidatedInput("Primary Phone         : ", "phone");
    cout << "Alternate Phone (Opt) : ";
    getline(cin, phone2);  // Optional field; user can leave it blank
    address = getValidatedInput("Address               : ", "");
    secQ = getValidatedInput("Security Question     : ", "");
    secA = getValidatedInput("Answer                : ", "");

    ofstream fout("data/staff.txt", ios::app);
    fout << id << "|" << name << "|" << uname << "|" << pass << "|" << gender << "|" << role << "|" << salary << "|"
         << doj << "|" << fname << "|" << mname << "|" << email << "|" << phone1 << "|" << phone2 << "|" << address << "|"
         << secQ << "|" << secA << "\n";
    fout.close();

    ofstream salaryFile("data/staff_salaries.txt", ios::app);
    salaryFile << uname << "|Unpaid\n";
    salaryFile.close();
    
    logAudit("Admin registered a new staff: " + uname);  // Audit log
    cout << "Staff registered successfully.\n";
    pauseAndContinue();
}

// ------------------ Register Guest by Admin ------------------
void registerGuestByAdmin() {
    printHeader("Register Guest (Admin)");
    string name, uname, pass, gender, email, phone, meal, secQ, secA;

    name = getValidatedInput("Guest Name          : ", "");

    while (true) {
        uname = getValidatedInput("Username            : ", "");
        if (uname == "cancel") return;
        if (!isUsernameUnique(uname)) {
            cout << "Username exists!\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Password            : ";
        pass = getMaskedPassword();
        if (pass.length() < 8) {
            cout << "Password must be at least 8 characters.\n";
            continue;
        }
        break;
    }

    gender = getValidatedInput("Gender (M/F)        : ", "");
    email = getValidatedInput("Email               : ", "email");
    phone = getValidatedInput("Phone               : ", "phone");
    meal = getValidatedInput("Meal Preference     : ", "");
    secQ = getValidatedInput("Security Question   : ", "");
    secA = getValidatedInput("Answer              : ", "");

    ofstream fout("data/guests.txt", ios::app);
    fout << name << "|" << uname << "|" << pass << "|" << gender << "|" << email << "|" << phone << "|" << meal << "|" << secQ << "|" << secA << "\n";
    fout.close();
    
    logAudit("Admin registered a new guest: " + uname);  // Audit log
    cout << "Guest registered by admin.\n";
    pauseAndContinue();
}

// ------------------ Admin Dashboard ------------------
void adminDashboard() {
    int choice;
    do {
        printHeader("Admin Dashboard");
        cout << "\n============= ADMIN CONTROL PANEL =============\n";
        cout << "1. Register Student\n";
        cout << "2. Register Staff\n";
        cout << "3. Manage Finance\n";
        cout << "4. Manage Inventory\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Attendance Summary\n";
        cout << "7. Generate Reports\n";
        cout << "8. Reset User Credentials\n";
        cout << "9. Edit Weekly Menu\n";
        cout << "10. Manage Holidays\n";
        cout << "11. Broadcast Message\n";
        cout << "12. View Notifications\n";
        cout << "13. View Feedbacks\n";
        cout << "14. View Enquiries\n";
        cout << "15. View Audit Log\n";
        cout << "16. Update Admin Profile\n";
        cout << "17. Exit and Logout\n";
        cout << "\n===============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: registerStaff(); break;
            case 3: financePanel(); break;
            case 4: inventoryPanel(); break;
            case 5: markAttendancePanel(); break;
            case 6: viewAttendanceSummary(); break;
            case 7: reportPanel(); break;
            case 8: resetUserCredentials(); break;
            case 9: editWeeklyMenu(); break;
            case 10: manageHolidays(); break;
            case 11: broadcastMessage(); break;
            case 12: viewNotifications(); break;
            case 13: viewFeedbacks(); break;
            case 14: viewEnquiries(); break;
            case 15: viewAuditLog(); break;
            case 16: updateAdminProfile(); break;
            case 17: cout << "\nLogout successful. Returning to main menu.\n"; return;
            default: cout << "Invalid choice. Please try again.\n"; pauseAndContinue();
        }
    } while (true);
}

// ------------------ Admin Dashboard Helper Functions ------------------//
// Reset user credentials for Student/Staff//
void resetUserCredentials() {
    printHeader("Reset User Credentials");

    cout << "1. Student\n";
    cout << "2. Staff\n";
    cout << "3. Guest\n";
    cout << "4. Cancel\n";
    cout << "\nSelect user type: ";
    int choice;
    cin >> choice;

    string role, file;
    int unameIndex = 2;
    switch (choice) {
        case 1: role = "Student"; file = "data/students.txt"; break;
        case 2: role = "Staff";   file = "data/staff.txt";    break;
        case 3: role = "Guest";   file = "data/guests.txt";   unameIndex = 1; break;
        case 4: return;
        default: cout << "Invalid choice.\n"; pauseAndContinue(); return;
    }

    string uname;
    cout << "\nEnter username of " << role << ": ";
    cin >> uname;
    cin.ignore();

    if (!isUsernameInFile(file, unameIndex, uname)) {
        cout << "User not found.\n"; pauseAndContinue(); return;
    }

    vector<string> updatedFields;

    if (role == "Student") {
        string id, name, pass, gender, branch, year, dues, doj, fname, mname, email, phone1, phone2, address, secQ, secA;
        cout << "ID                : "; getline(cin, id);
        cout << "Full Name         : "; getline(cin, name);
        cout << "Password          : "; pass = getMaskedPassword();
        cout << "Gender (M/F)      : "; getline(cin, gender);
        cout << "Branch            : "; getline(cin, branch);
        cout << "Year              : "; getline(cin, year);
        cout << "Dues Rs.            : "; getline(cin, dues);
        cout << "Joining Date      : "; getline(cin, doj);
        cout << "Father's Name     : "; getline(cin, fname);
        cout << "Mother's Name     : "; getline(cin, mname);
        cout << "Email             : "; getline(cin, email);
        cout << "Primary Phone     : "; getline(cin, phone1);
        cout << "Alternate Phone   : "; getline(cin, phone2);
        cout << "Address           : "; getline(cin, address);
        cout << "Security Question : "; getline(cin, secQ);
        cout << "Answer            : "; getline(cin, secA);

        updatedFields = {id, name, uname, pass, gender, branch, year, dues, doj, fname, mname, email, phone1, phone2, address, secQ, secA};
    }
    else if (role == "Staff") {
        string id, name, pass, gender, role_, salary, doj, fname, mname, email, phone1, phone2, address, secQ, secA;
        cout << "ID                : "; getline(cin, id);
        cout << "Full Name         : "; getline(cin, name);
        cout << "Password          : "; pass = getMaskedPassword();
        cout << "Gender (M/F)      : "; getline(cin, gender);
        cout << "Role              : "; getline(cin, role_);
        cout << "Salary Rs.          : "; getline(cin, salary);
        cout << "Joining Date      : "; getline(cin, doj);
        cout << "Father's Name     : "; getline(cin, fname);
        cout << "Mother's Name     : "; getline(cin, mname);
        cout << "Email             : "; getline(cin, email);
        cout << "Primary Phone     : "; getline(cin, phone1);
        cout << "Alternate Phone   : "; getline(cin, phone2);
        cout << "Address           : "; getline(cin, address);
        cout << "Security Question : "; getline(cin, secQ);
        cout << "Answer            : "; getline(cin, secA);

        updatedFields = {id, name, uname, pass, gender, role_, salary, doj, fname, mname, email, phone1, phone2, address, secQ, secA};
    }
    else if (role == "Guest") {
        string name, pass, gender, email, phone, meal, secQ, secA;
        cout << "Name              : "; getline(cin, name);
        cout << "Password          : "; pass = getMaskedPassword();
        cout << "Gender (M/F)      : "; getline(cin, gender);
        cout << "Email             : "; getline(cin, email);
        cout << "Phone             : "; getline(cin, phone);
        cout << "Meal Preference   : "; getline(cin, meal);
        cout << "Security Question : "; getline(cin, secQ);
        cout << "Answer            : "; getline(cin, secA);

        updatedFields = {name, uname, pass, gender, email, phone, meal, secQ, secA};
    }

    // Rewrite data file with updated record
    ifstream fin(file);
    ofstream fout("data/temp.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);

        if (fields[unameIndex] == uname) {
            for (size_t i = 0; i < updatedFields.size(); ++i) {
                fout << updatedFields[i];
                if (i != updatedFields.size() - 1) fout << "|";
            }
        } else {
            fout << line;
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    remove(file.c_str());
    rename("data/temp.txt", file.c_str());

    cout << " " << role << " data updated successfully.\n";
    pauseAndContinue();
}

// Admin edits the full weekly menu (Breakfast, Lunch, Dinner)
void editWeeklyMenu() {
    printHeader("Edit Weekly Menu (All Slots)");

    const vector<string> days = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };
    const vector<string> slots = { "Breakfast", "Lunch", "Dinner" };

    map<string, map<string, string>> menu;  // day -> slot -> meal

    // Load existing menu if present
    ifstream fin("data/weekly_menu.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string day, slot, meal;
        getline(ss, day, '|');
        getline(ss, slot, '|');
        getline(ss, meal);
        menu[day][slot] = meal;
    }
    fin.close();

    // Edit each slot for each day
    for (const string& day : days) {
        for (const string& slot : slots) {
            cout << "\n" << day << " - " << slot << " (current: ";
            if (!menu[day][slot].empty())
                cout << menu[day][slot];
            else
                cout << "not set";
            cout << ")\nNew meal (leave blank to keep): ";
            string meal;
            getline(cin, meal);
            if (!meal.empty()) menu[day][slot] = meal;
        }
    }

    // Save updated menu
    ofstream fout("data/weekly_menu.txt");
    for (const auto& d : days) {
        for (const auto& s : slots) {
            fout << d << "|" << s << "|" << menu[d][s] << "\n";
        }
    }
    fout.close();

    cout << "\nWeekly multi-slot menu updated.\n";
    pauseAndContinue();
}

// Admin manages holiday calendar
void manageHolidays() {
    printHeader("Manage Holidays");

    vector<string> holidays;
    string line;

    // Load holidays
    ifstream fin("data/holidays.txt");
    while (getline(fin, line)) {
        holidays.push_back(line);
    }
    fin.close();

    int choice;
    do {
        clearScreen();
        printHeader("Manage Holidays");

        cout << "Current Holidays:\n";
        if (holidays.empty()) {
            cout << "No holidays recorded.\n";
        } else {
            for (size_t i = 0; i < holidays.size(); ++i) {
                cout << i + 1 << ". " << holidays[i] << "\n";
            }
        }

        cout << "\nMenu:\n";
        cout << "1. Add Holiday\n";
        cout << "2. Delete Holiday\n";
        cout << "3. Back to Dashboard\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string newHoliday;
            cout << "Enter holiday (e.g., 15-08-2025 | Independence Day): ";
            getline(cin, newHoliday);
            holidays.push_back(newHoliday);
            cout << "Holiday added.\n";
            pauseAndContinue();
        } else if (choice == 2) {
            int delIndex;
            cout << "Enter holiday number to delete: ";
            cin >> delIndex;
            if (delIndex > 0 && delIndex <= holidays.size()) {
                holidays.erase(holidays.begin() + delIndex - 1);
                cout << "Holiday deleted.\n";
            } else {
                cout << "Invalid index.\n";
            }
            pauseAndContinue();
        } else if (choice != 3) {
            cout << "Invalid choice.\n";
            pauseAndContinue();
        }

    } while (choice != 3);

    // Save updated holidays
    ofstream fout("data/holidays.txt");
    for (const string& h : holidays) {
        fout << h << "\n";
    }
    fout.close();
}


void broadcastMessage()     { cout << "[TODO] Broadcast message\n"; pauseAndContinue(); }
void viewNotifications()    { cout << "[TODO] View notifications\n"; pauseAndContinue(); }

void viewAuditLog() {
    printHeader("Audit Log");

    ifstream fin("data/audit_log.txt");
    string line;
    int count = 0;

    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }

    if (count == 0) cout << "No audit logs available.\n";

    fin.close();
    pauseAndContinue();
}

void updateAdminProfile()   { cout << "[TODO] Update admin profile\n"; pauseAndContinue(); }

// Admin marks attendance for students/staff
void markAttendancePanel() {
    printHeader("Mark Attendance Panel");

    int roleChoice;
    cout << "Select Role to Mark Attendance:\n";
    cout << "1. Student\n";
    cout << "2. Staff\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
    cin >> roleChoice;
    cin.ignore();

    if (roleChoice != 1 && roleChoice != 2) return;

    if (isTodayHoliday()) {
        cout << "Attendance cannot be marked. Today is a holiday (" << getTodayDate() << ").\n";
        pauseAndContinue();
        return;
    }

    string file = (roleChoice == 1) ? "data/students.txt" : "data/staff.txt";
    string attendanceFile = (roleChoice == 1) ? "data/attendance_student.txt" : "data/attendance_staff.txt";

    ifstream fin(file);
    ofstream fout(attendanceFile, ios::app);
    string line;
    vector<string> usernames;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);
        if (fields.size() >= 3) usernames.push_back(fields[2]);
    }
    fin.close();

    for (const string& uname : usernames) {
        string mark;
        cout << "Mark attendance for " << uname << " (Y/N): ";
        getline(cin, mark);
        if (mark == "Y" || mark == "y") {
            fout << uname << "|" << getTodayDate() << "\n";
        }
    }

    fout.close();
    cout << "Attendance marking completed.\n";
    pauseAndContinue();
}

// Admin views attendance summary for students/staff
void viewAttendanceSummary() {
    printHeader("Attendance Summary");

    int reportType;
    cout << "1. Daily Summary\n";
    cout << "2. Monthly Summary\n";
    cout << "3. Date Range Summary\n";
    cout << "4. Back\n";
    cout << "Choose summary type: ";
    cin >> reportType;

    if (reportType == 4) return;

    int userType;
    cout << "\n1. Student\n";
    cout << "2. Staff\n";
    cout << "Choose user type: ";
    cin >> userType;

    string file = (userType == 1) ? "data/attendance_student.txt" : "data/attendance_staff.txt";
    string label = (userType == 1) ? "Student" : "Staff";

    ifstream fin(file);
    vector<string> records;
    string line;
    while (getline(fin, line)) records.push_back(line);
    fin.close();

    cin.ignore();
    if (reportType == 1) {
        // Daily
        string date;
        cout << "\nEnter date (DD-MM-YYYY): ";
        getline(cin, date);
        cout << "\n" << label << " Attendance on " << date << ":\n";
        int count = 0;
        for (auto& r : records) {
            if (r.find("|" + date) != string::npos) {
                cout << "- " << r.substr(0, r.find('|')) << "\n";
                count++;
            }
        }
        cout << "\nTotal: " << count << " present\n";
    }
    else if (reportType == 2) {
        // Monthly
        string monthYear;
        cout << "\nEnter month and year (MM-YYYY): ";
        getline(cin, monthYear);
        map<string, int> counter;
        for (auto& r : records) {
            size_t pos = r.find('|');
            if (pos != string::npos && r.substr(pos + 4, 7) == monthYear) {
                counter[r.substr(0, pos)]++;
            }
        }
        cout << "\nMonthly Attendance (" << label << "):\n";
        for (auto& [name, val] : counter) {
            cout << "- " << name << " : " << val << " days\n";
        }
    }
    else if (reportType == 3) {
        // Date Range
        string from, to;
        cout << "\nFrom (DD-MM-YYYY): "; getline(cin, from);
        cout << "To   (DD-MM-YYYY): "; getline(cin, to);
        cout << "\nAttendance from " << from << " to " << to << " (" << label << "):\n";
        for (auto& r : records) {
            size_t pos = r.find('|');
            if (pos != string::npos) {
                string uname = r.substr(0, pos);
                string date = r.substr(pos + 1);
                if (isDateInRange(date, from, to)) {
                    cout << "- " << uname << " on " << date << "\n";
                }
            }
        }
    } else {
        cout << "Invalid report type.\n";
    }

    pauseAndContinue();
}



