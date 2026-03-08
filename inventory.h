// inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

// Admin inventory control panel
void inventoryPanel();

// Inventory operations
void addInventoryItem();                   // Add new stock
void viewInventory();                      // View all items
void searchInventoryItem();                // Search item by name
void issueInventoryItem();                 // Reduce quantity from stock
void deleteExpiredItems();                 // Optional: remove old items
void exportInventoryToCSV();               // Optional: for printing or records

#endif
