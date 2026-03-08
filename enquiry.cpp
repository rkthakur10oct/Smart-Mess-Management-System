// enquiry.cpp
#include "enquiry.h"
#include "ui.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Student/Staff/Guest submits an enquiry to admin
void submitEnquiry(const string& username, const string& role) {
    printHeader("Submit Enquiry");

    string message;
    cin.ignore();  // Clear newline
    cout << "Enter your enquiry message:\n> ";
    getline(cin, message);

    ofstream fout("data/enquiries.txt", ios::app);
    fout << role << ":" << username << "|" << message << "|Pending\n";
    fout.close();

    cout << "\nEnquiry submitted to Admin.\n";
    pauseAndContinue();
}

// Admin views all enquiries
void viewEnquiries() {
    printHeader("View Enquiries");

    ifstream fin("data/enquiries.txt");
    string line;
    int count = 0;
    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }

    if (count == 0) cout << "No enquiries found.\n";
    fin.close();

    pauseAndContinue();
}

// Admin responds to enquiries (mark as Seen)
void respondToEnquiries() {
    printHeader("Respond to Enquiries");

    ifstream fin("data/enquiries.txt");
    vector<string> enquiries;
    string line;

    while (getline(fin, line)) enquiries.push_back(line);
    fin.close();

    if (enquiries.empty()) {
        cout << "No enquiries available.\n";
        pauseAndContinue();
        return;
    }

    // Display all enquiries
    for (size_t i = 0; i < enquiries.size(); ++i) {
        cout << i + 1 << ". " << enquiries[i] << "\n";
    }

    int choice;
    cout << "\nEnter enquiry number to mark as Seen (0 to cancel): ";
    cin >> choice;

    ofstream fout("data/temp_enquiries.txt");

    for (size_t i = 0; i < enquiries.size(); ++i) {
        if ((int)i + 1 == choice) {
            size_t pos = enquiries[i].rfind("|");
            if (pos != string::npos) {
                enquiries[i] = enquiries[i].substr(0, pos) + "|Seen";
            }
        }
        fout << enquiries[i] << "\n";
    }

    fout.close();
    remove("data/enquiries.txt");
    rename("data/temp_enquiries.txt", "data/enquiries.txt");

    cout << "Enquiry status updated.\n";
    pauseAndContinue();
}
