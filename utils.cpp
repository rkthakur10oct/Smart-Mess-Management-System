// utils.cpp - Cross-platform utilities for Smart Mess Management System
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <regex>
#include <vector>
#include <sstream>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

// Reads a password securely from the console with masked input (*)
string getMaskedPassword() {
    string password;
    char ch;
    cout << "(input hidden): ";

#ifdef _WIN32
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
#else
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n') {
        if (ch == 127 || ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    cout << endl;
    return password;
}

// Removes whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Prompts user for validated input with format checking
string getValidatedInput(const string& prompt, const string& type) {
    string input;
    regex pattern;

    if (type == "email") pattern = regex("^[\\w.-]+@[\\w.-]+\\.[A-Za-z]{2,}$");
    else if (type == "phone") pattern = regex("^[0-9]{10}$");
    else if (type == "date") pattern = regex("^\\d{2}-\\d{2}-\\d{4}$");

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (input == "cancel" || input == "back") return input;
        if (input.empty()) {
            cout << "This field is mandatory. Please enter a value.\n";
        } else if (!type.empty() && !regex_match(input, pattern)) {
            cout << "Invalid format. Expected " << type << ". Try again or type 'cancel'.\n";
        } else {
            return input;
        }
    }
}

// Returns today's date in DD-MM-YYYY format
string getTodayDate() {
    time_t now = time(0);
    tm* t = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", t);
    return string(buffer);
}

// Returns a future date (offset by X days) in DD-MM-YYYY format
string getFutureDate(int offset) {
    time_t now = time(0) + offset * 24 * 60 * 60;
    tm* t = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", t);
    return string(buffer);
}

// Searches for a username in a file by its index field
bool isUsernameInFile(const string& file, int usernameIndex, const string& username) {
    ifstream fin(file);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string field;
        int index = 0;
        while (getline(ss, field, '|')) {
            if (index == usernameIndex && field == username) {
                return true;
            }
            index++;
        }
    }
    return false;
}

// Checks across all user files to ensure username is unique
bool isUsernameUnique(const string& username) {
    return !(
        isUsernameInFile("data/admin.dat", 0, username) ||
        isUsernameInFile("data/students.txt", 2, username) ||
        isUsernameInFile("data/staff.txt", 2, username) ||
        isUsernameInFile("data/guests.txt", 2, username)
    );
}

// Validates user's secret answer from a file based on username
bool verifySecretQA(const string& file, int unameIndex, const string& username) {
    ifstream fin(file);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);

        if (fields.size() >= 10 && fields[unameIndex] == username) {
            cout << "Security Question: " << fields[fields.size() - 2] << "\nAnswer: ";
            string answer;
            cin.ignore();
            getline(cin, answer);
            return (answer == fields.back());
        }
    }
    return false;
}

// Updates password for a specific user by rewriting file
bool updatePasswordInFile(const string& file, int usernameIndex, const string& username, const string& newPassword) {
    ifstream fin(file);
    ofstream fout("data/temp.txt");
    string line;
    bool updated = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);

        if (fields.size() > usernameIndex && fields[usernameIndex] == username) {
            fields[usernameIndex + 1] = newPassword;
            updated = true;
        }

        for (size_t i = 0; i < fields.size(); ++i) {
            fout << fields[i];
            if (i != fields.size() - 1) fout << "|";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    remove(file.c_str());
    rename("data/temp.txt", file.c_str());

    return updated;
}
// Checks if today is a holiday by reading from holidays.txt
bool isTodayHoliday() {
    string today = getTodayDate();
    ifstream fin("data/holidays.txt");
    string line;
    while (getline(fin, line)) {
        if (line.find(today) != string::npos) {
            return true;
        }
    }
    return false;
}



// Checks if a given date is within a specified range
bool isDateInRange(const std::string& target, const std::string& from, const std::string& to) {
    auto toInt = [](const std::string& d) {
        // Convert DD-MM-YYYY → YYYYMMDD for easy numeric comparison
        return stoi(d.substr(6, 4) + d.substr(3, 2) + d.substr(0, 2));
    };
    int t = toInt(target), f = toInt(from), u = toInt(to);
    return t >= f && t <= u;
}

// Logs an action to the audit log file with a timestamp
void logAudit(const std::string& action) {
    ofstream fout("data/audit_log.txt", ios::app);
    time_t now = time(0);
    tm* t = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
    fout << "[" << timestamp << "] " << action << "\n";
    fout.close();
}
