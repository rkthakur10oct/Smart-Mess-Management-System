// inventory.cpp
#include "inventory.h"
#include "ui.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

// Add a new inventory item (with retry, confirmation, and unit)
void addInventoryItem() {
    string itemName, vendor, expiryDate, unit;
    int quantity;
    char confirm;

    do {
        printHeader("Add Inventory Item");

        cin.ignore();
        cout << "Item Name     : "; getline(cin, itemName);
        cout << "Vendor Name   : "; getline(cin, vendor);
        cout << "Expiry Date   : "; getline(cin, expiryDate);  // Format: DD-MM-YYYY
        cout << "Quantity      : "; cin >> quantity;
        cin.ignore();
        cout << "Unit (kg/litre/packet/etc): "; getline(cin, unit);

        printHeader("Confirm Inventory Details");
        cout << "Item Name     : " << itemName << "\n";
        cout << "Vendor Name   : " << vendor << "\n";
        cout << "Expiry Date   : " << expiryDate << "\n";
        cout << "Quantity      : " << quantity << " " << unit << "\n";

        cout << "\nDo you want to save this entry? (Y/N/R to retry): ";
        cin >> confirm;
        confirm = tolower(confirm);

        if (confirm == 'y') {
            ofstream fout("data/inventory.txt", ios::app);
            fout << itemName << "|" << vendor << "|" << expiryDate << "|" << quantity << " " << unit << "\n";
            fout.close();
            cout << "Item added to inventory.\n";
            pauseAndContinue();
            break;
        } else if (confirm == 'n') {
            cout << "Entry discarded.\n";
            pauseAndContinue();
            break;
        } else if (confirm == 'r') {
            cout << "Let's try again.\n";
        } else {
            cout << "Invalid option. Returning to inventory panel.\n";
            pauseAndContinue();
            break;
        }
    } while (true);
}

// View all inventory items
void viewInventory() {
    printHeader("Inventory List");

    ifstream fin("data/inventory.txt");
    string line;
    int count = 0;

    while (getline(fin, line)) {
        cout << ++count << ". " << line << "\n";
    }

    if (count == 0) cout << "No inventory items found.\n";
    fin.close();

    pauseAndContinue();
}

// Search for an item by name
void searchInventoryItem() {
    printHeader("Search Inventory");

    string searchTerm;
    cin.ignore();
    cout << "Enter item name to search: ";
    getline(cin, searchTerm);

    ifstream fin("data/inventory.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        if (line.find(searchTerm) != string::npos) {
            cout << "Found: " << line << "\n";
            found = true;
        }
    }

    if (!found) cout << "Item not found.\n";
    fin.close();

    pauseAndContinue();
}

// Issue quantity of item (reduce stock)
void issueInventoryItem() {
    printHeader("Issue Inventory Item");

    string itemName;
    int quantityToIssue;
    cin.ignore();
    cout << "Item Name to Issue: "; getline(cin, itemName);
    cout << "Quantity to Issue : "; cin >> quantityToIssue;

    ifstream fin("data/inventory.txt");
    ofstream fout("data/temp_inventory.txt");

    string line;
    bool updated = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        string name, vendor, expiry, qtyStr;
        getline(ss, name, '|');
        getline(ss, vendor, '|');
        getline(ss, expiry, '|');
        getline(ss, qtyStr, '|');

        int qty = stoi(qtyStr);

        if (name == itemName) {
            if (qty >= quantityToIssue) {
                qty -= quantityToIssue;
                updated = true;
                cout << "Issued " << quantityToIssue << " units of " << name << ".\n";
            } else {
                cout << "Not enough stock to issue.\n";
            }
        }

        fout << name << "|" << vendor << "|" << expiry << "|" << qty << "\n";
    }

    fin.close();
    fout.close();

    remove("data/inventory.txt");
    rename("data/temp_inventory.txt", "data/inventory.txt");

    if (!updated) cout << "Item not found or stock insufficient.\n";

    pauseAndContinue();
}

// Inventory Control Panel
void inventoryPanel() {
    int choice;
    do {
        printHeader("Inventory Management");

        cout << "1. Add Item\n";
        cout << "2. View Inventory\n";
        cout << "3. Search Item\n";
        cout << "4. Issue Item\n";
        cout << "5. Back to Admin Dashboard\n";
        cout << "\nSelect option: ";
        cin >> choice;

        switch (choice) {
            case 1: addInventoryItem(); break;
            case 2: viewInventory(); break;
            case 3: searchInventoryItem(); break;
            case 4: issueInventoryItem(); break;
            case 5: return;
            default: cout << "Invalid option!\n"; pauseAndContinue();
        }
    } while (true);
}
