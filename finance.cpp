// finance.cpp
#include "finance.h"
#include "ui.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Adds an income or expense transaction
void addTransaction(const string& type) {
    printHeader("Add " + type);

    string date, source;
    float amount;

    cin.ignore();
    cout << "Date (DD-MM-YYYY): "; getline(cin, date);
    cout << type << " Source/Description: "; getline(cin, source);
    cout << "Amount (Rs.): "; cin >> amount;

    ofstream fout("data/finance.txt", ios::app);
    fout << type << "|" << date << "|" << source << "|" << fixed << setprecision(2) << amount << "\n";
    fout.close();

    cout << " " << type << " recorded.\n";
    pauseAndContinue();
}

// Views all finance transactions
void viewTransactions() {
    printHeader("All Finance Transactions");

    ifstream fin("data/finance.txt");
    string line;
    int count = 0;

    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }

    if (count == 0) cout << "No transactions found.\n";
    fin.close();
    pauseAndContinue();
}

// Shows total income, expenses, and net profit/loss
void viewProfitLoss() {
    printHeader("Finance Summary");

    ifstream fin("data/finance.txt");
    string line;
    float income = 0, expense = 0;

    while (getline(fin, line)) {
        stringstream ss(line);
        string type, date, source, amtStr;
        getline(ss, type, '|');
        getline(ss, date, '|');
        getline(ss, source, '|');
        getline(ss, amtStr, '|');
        float amount = stof(amtStr);

        if (type == "Income") income += amount;
        else if (type == "Expense") expense += amount;
    }

    float balance = income - expense;
    cout << fixed << setprecision(2);
    cout << "Total Income  : Rs." << income << "\n";
    cout << "Total Expense : Rs." << expense << "\n";
    cout << (balance >= 0 ? "Net Profit    : Rs." : "Net Loss      : ₹") << abs(balance) << "\n";

    fin.close();
    pauseAndContinue();
}

// Finance control panel for admin
void financePanel() {
    int choice;
    do {
        printHeader("Finance Panel");

        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. View Profit/Loss Summary\n";
        cout << "5. Back to Admin Dashboard\n";
        cout << "\nSelect option: ";
        cin >> choice;

        switch (choice) {
            case 1: addTransaction("Income"); break;
            case 2: addTransaction("Expense"); break;
            case 3: viewTransactions(); break;
            case 4: viewProfitLoss(); break;
            case 5: return;
            default: cout << "Invalid choice!\n"; pauseAndContinue();
        }
    } while (true);
}
