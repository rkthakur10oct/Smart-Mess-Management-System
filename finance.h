// finance.h
#ifndef FINANCE_H
#define FINANCE_H

#include <string>  // REQUIRED for std::string

// Admin-side finance control panel
void financePanel();

// Internal utilities for finance module
void addTransaction(const std::string& type);  // Income or Expense
void viewTransactions();
void viewProfitLoss();

#endif
