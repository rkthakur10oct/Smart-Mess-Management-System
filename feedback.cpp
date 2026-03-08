// feedback.cpp - Feedback system for users and admin
#include "feedback.h"
#include "ui.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Submit feedback (Student/Staff/Guest)
void submitFeedback(const string& username, const string& role) {
    printHeader("Submit Feedback");
    string feedback;
    cin.ignore();
    cout << "Enter your feedback message:\n> ";
    getline(cin, feedback);

    ofstream fout("data/feedback.txt", ios::app);
    fout << role << ":" << username << "|" << feedback << "|Pending\n";
    fout.close();

    cout << "\nFeedback submitted to Admin.\n";
    pauseAndContinue();
}

// View all feedbacks (raw)
void viewAllFeedback() {
    printHeader("All Feedbacks");
    ifstream fin("data/feedback.txt");
    string line;
    int count = 0;
    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }
    if (count == 0) cout << "No feedbacks found.\n";
    fin.close();
    pauseAndContinue();
}

// Admin views and manages feedbacks
void viewFeedbacks() {
    printHeader("All Pending Feedbacks");
    vector<string> allLines;
    vector<int> pendingIndexes;
    string line;
    int index = 0;

    ifstream fin("data/feedback.txt");
    while (getline(fin, line)) {
        allLines.push_back(line);
        stringstream ss(line);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);
        if (fields.size() == 3 && fields[2] == "Pending") {
            pendingIndexes.push_back(index);
        }
        index++;
    }
    fin.close();

    if (pendingIndexes.empty()) {
        cout << "No pending feedbacks.\n";
        pauseAndContinue();
        return;
    }

    for (int i = 0; i < pendingIndexes.size(); ++i) {
        stringstream ss(allLines[pendingIndexes[i]]);
        vector<string> fields;
        string token;
        while (getline(ss, token, '|')) fields.push_back(token);
        string role = fields[0].substr(0, 3);
        string user = fields[0].substr(4);
        cout << i + 1 << ". [" << role << "] " << user << ": " << fields[1] << "\n";
    }

    int choice;
    cout << "\nEnter feedback number to manage (0 to cancel): ";
    cin >> choice;
    if (choice < 1 || choice > (int)pendingIndexes.size()) {
        cout << "Cancelled.\n";
        pauseAndContinue();
        return;
    }

    int lineIndex = pendingIndexes[choice - 1];
    stringstream ss(allLines[lineIndex]);
    vector<string> fields;
    string token;
    while (getline(ss, token, '|')) fields.push_back(token);

    cout << "\nSelected Feedback:\n" << fields[1] << "\n";
    cout << "\n1. Mark as Reviewed\n";
    cout << "2. Delete Feedback\n";
    cout << "3. Respond to Feedback\n";
    cout << "4. Cancel\n";
    cout << "Enter option: ";
    int action;
    cin >> action;
    cin.ignore();

    switch (action) {
        case 1:
            fields[2] = "Reviewed";
            break;
        case 2:
            allLines.erase(allLines.begin() + lineIndex);
            break;
        case 3: {
            string response;
            cout << "Enter your response: ";
            getline(cin, response);
            ofstream out("data/feedback_responses.txt", ios::app);
            out << fields[0] << "|" << fields[1] << "|" << response << "|" << getTodayDate() << "\n";
            out.close();
            fields[2] = "Reviewed";
            break;
        }
        case 4:
        default:
            cout << "Action cancelled.\n";
            pauseAndContinue();
            return;
    }

    ofstream fout("data/feedback.txt");
    for (int i = 0; i < (int)allLines.size(); ++i) {
        if (i == lineIndex && action != 2) {
            for (size_t j = 0; j < fields.size(); ++j) {
                fout << fields[j];
                if (j != fields.size() - 1) fout << "|";
            }
            fout << "\n";
        } else if (i != lineIndex || action == 2) {
            fout << allLines[i] << "\n";
        }
    }
    fout.close();

    cout << "Feedback updated.\n";
    pauseAndContinue();
}

// User views their own feedback status and response
void viewOwnFeedback(const string& username, const string& role) {
    printHeader("Your Submitted Feedback");

    ifstream fin("data/feedback.txt");
    string line;
    bool found = false;
    string prefix = role + ":" + username;

    while (getline(fin, line)) {
        if (line.find(prefix) == 0) {
            found = true;
            stringstream ss(line);
            vector<string> fields;
            string token;
            while (getline(ss, token, '|')) fields.push_back(token);

            cout << "\nFeedback: " << fields[1] << "\nStatus  : " << fields[2] << "\n";

            ifstream responseFile("data/feedback_responses.txt");
            string respLine;
            while (getline(responseFile, respLine)) {
                stringstream rs(respLine);
                vector<string> rfields;
                string rtoken;
                while (getline(rs, rtoken, '|')) rfields.push_back(rtoken);

                if (rfields.size() >= 4 && rfields[0] == prefix && rfields[1] == fields[1]) {
                    cout << "Response : " << rfields[2] << "\nDate     : " << rfields[3] << "\n";
                    break;
                }
            }
            responseFile.close();
        }
    }

    if (!found) cout << "You haven't submitted any feedback yet.\n";
    fin.close();
    pauseAndContinue();
}

// Optional bulk update for simple marking
void respondToFeedback() {
    printHeader("Respond to Feedback (Simple)");
    ifstream fin("data/feedback.txt");
    vector<string> feedbacks;
    string line;

    while (getline(fin, line)) feedbacks.push_back(line);
    fin.close();

    if (feedbacks.empty()) {
        cout << "No feedback to respond to.\n";
        pauseAndContinue();
        return;
    }

    for (size_t i = 0; i < feedbacks.size(); ++i) {
        cout << i + 1 << ". " << feedbacks[i] << "\n";
    }

    int choice;
    cout << "\nEnter feedback number to mark as Seen (0 to cancel): ";
    cin >> choice;

    ofstream fout("data/temp_feedback.txt");
    for (size_t i = 0; i < feedbacks.size(); ++i) {
        if ((int)i + 1 == choice) {
            size_t pos = feedbacks[i].rfind("|");
            if (pos != string::npos) {
                feedbacks[i] = feedbacks[i].substr(0, pos) + "|Seen";
            }
        }
        fout << feedbacks[i] << "\n";
    }

    fout.close();
    remove("data/feedback.txt");
    rename("data/temp_feedback.txt", "data/feedback.txt");

    cout << "Feedback marked as Seen.\n";
    pauseAndContinue();
}


// Allow a student, staff, or guest to update or delete their own feedback if it's still pending
void manageOwnFeedback(const string& username, const string& role) {
    printHeader("Manage Your Feedback");

    // Load all feedback entries from file
    vector<string> allFeedbacks;
    ifstream fin("data/feedback.txt");
    string line;
    while (getline(fin, line)) allFeedbacks.push_back(line);
    fin.close();

    // Collect indexes of feedbacks belonging to this user that are still pending
    vector<int> userIndexes;
    string prefix = role + ":" + username;
    for (int i = 0; i < (int)allFeedbacks.size(); ++i) {
        if (allFeedbacks[i].find(prefix) == 0 && allFeedbacks[i].rfind("|Pending") != string::npos)
            userIndexes.push_back(i);
    }

    if (userIndexes.empty()) {
        cout << "No editable feedbacks found.\n";
        pauseAndContinue();
        return;
    }

    // Display user's editable feedbacks with index numbers
    for (int i = 0; i < (int)userIndexes.size(); ++i) {
        stringstream ss(allFeedbacks[userIndexes[i]]);
        vector<string> parts;
        string token;
        while (getline(ss, token, '|')) parts.push_back(token);
        cout << i + 1 << ". " << parts[1] << " [Status: " << parts[2] << "]\n";
    }

    // Prompt user to choose a feedback entry to update or delete
    int choice;
    cout << "\nSelect feedback to edit/delete (0 to cancel): ";
    cin >> choice;
    cin.ignore();
    if (choice <= 0 || choice > (int)userIndexes.size()) {
        cout << "Cancelled.\n"; pauseAndContinue(); return;
    }

    // Parse the selected feedback
    int index = userIndexes[choice - 1];
    stringstream ss(allFeedbacks[index]);
    vector<string> parts;
    string token;
    while (getline(ss, token, '|')) parts.push_back(token);

    // Show options: edit or delete
    cout << "\n1. Edit Feedback\n2. Delete Feedback\n3. Cancel\nEnter choice: ";
    int action; cin >> action; cin.ignore();

    if (action == 1) {
        // Allow editing feedback text
        cout << "Enter new feedback:\n> ";
        string newMsg; getline(cin, newMsg);
        allFeedbacks[index] = parts[0] + "|" + newMsg + "|Pending";
        cout << "Feedback updated.\n";
    } else if (action == 2) {
        // Remove selected feedback from list
        allFeedbacks.erase(allFeedbacks.begin() + index);
        cout << "Feedback deleted.\n";
    } else {
        cout << "Cancelled.\n"; pauseAndContinue(); return;
    }

    // Save updated feedbacks back to file
    ofstream fout("data/feedback.txt");
    for (auto& f : allFeedbacks) fout << f << "\n";
    fout.close();

    pauseAndContinue();
}
