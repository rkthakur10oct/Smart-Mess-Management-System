// guest.cpp
#include "guest.h"
#include "ui.h"
#include "utils.h"
#include "feedback.h"
#include "enquiry.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

//guestDashboard
void guestDashboard(const string& username) {
    printHeader("Guest Dashboard");
    cout << "Welcome, Guest: " << username << endl;
    pauseAndContinue();
}


// Guest Menu Panel
void guestMenu(const string& guestId) {
    int choice;
    do {
        printHeader("Guest Dashboard");
        cout << "1. View Profile\n";
        cout << "2. View Weekly Menu\n";
        cout << "3. Submit Feedback\n";
        cout << "4. Submit Enquiry\n";
        cout << "5. Download Meal Receipt\n";
        cout << "6. View My Feedback Status\n";
        cout << "7. Manage My Feedback\n";
        cout << "8. Logout\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewGuestProfile(guestId); break;
            case 2: viewWeeklyMenu(); break;
            case 3: submitFeedback(guestId, "GUEST"); break;
            case 4: submitEnquiry(guestId, "GUEST"); break;
            case 5: downloadGuestReceipt(guestId); break;
            case 6: viewOwnFeedback(guestId, "GUEST"); break;
            case 7: manageOwnFeedback(guestId, "GUEST"); break;
            case 8: cout << "Logging out...\n"; return;
            default: cout << "Invalid choice!\n"; pauseAndContinue();
        }
    } while (true);
}

// View Guest Profile
void viewGuestProfile(const string& guestId) {
    printHeader("Guest Profile");

    ifstream fin("data/guests.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, '|')) fields.push_back(field);

        if (fields.size() > 8 && fields[2] == guestId) {
            found = true;
            cout << "Guest ID   : " << fields[0] << "\n";
            cout << "Full Name  : " << fields[1] << "\n";
            cout << "Gender     : " << fields[4] << "\n";
            cout << "Meal Type  : " << fields[5] << "\n";
            cout << "Email      : " << fields[6] << "\n";
            cout << "Contact    : " << fields[7] << "\n";
            cout << "Joined On  : " << fields[8] << "\n";
            break;
        }
    }

    if (!found) cout << "Guest not found!\n";
    fin.close();
    pauseAndContinue();
}

// View Weekly Menu
void viewWeeklyMenu() {
    printHeader("Weekly Menu");

    ifstream fin("data/weekly_menu.txt");
    string line;
    while (getline(fin, line)) cout << line << "\n";
    fin.close();

    pauseAndContinue();
}

// Download Meal Receipt
void downloadGuestReceipt(const string& guestId) {
    printHeader("Download Receipt");

    ifstream fin("data/guests.txt");
    string line, receipt;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, '|')) fields.push_back(field);

        if (fields.size() > 8 && fields[2] == guestId) {
            found = true;
            receipt += "-----------------------------\n";
            receipt += "     GUEST MEAL RECEIPT\n";
            receipt += "-----------------------------\n";
            receipt += "Name       : " + fields[1] + "\n";
            receipt += "ID         : " + fields[0] + "\n";
            receipt += "Meal Type  : " + fields[5] + "\n";
            receipt += "Date       : " + getTodayDate() + "\n";
            receipt += "Contact    : " + fields[7] + "\n";
            receipt += "-----------------------------\n";
            receipt += "   Thank you! Jai Hind 🇮🇳\n";
            break;
        }
    }

    fin.close();

    if (found) {
        string path = "receipts/guest_meal_receipts/" + guestId + "_receipt.txt";
        ofstream fout(path);
        fout << receipt;
        fout.close();
        cout << "Receipt saved to: " << path << "\n";
    } else {
        cout << "Guest not found!\n";
    }

    pauseAndContinue();
}
