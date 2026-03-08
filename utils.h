#ifndef UTILS_H
#define UTILS_H

#include <string>

// UI utility functions
std::string getMaskedPassword();                  // Hide password input
std::string getTodayDate();                       // Get current date (DD-MM-YYYY)
std::string getFutureDate(int days);              // Get future date (DD-MM-YYYY)
std::string trim(const std::string& str);         // Reusable trimming
std::string getValidatedInput(const std::string& prompt, const std::string& type); // ✅ Added validated input

// Logging utility
void logAudit(const std::string& action);

// Username validation
bool isUsernameUnique(const std::string& username);
bool isUsernameInFile(const std::string& file, int usernameIndex, const std::string& username);
bool isTodayHoliday(); // Checks if today is marked as holiday

// File operations
bool updatePasswordInFile(const std::string& file, int usernameIndex, const std::string& username, const std::string& newPassword);
bool verifySecretQA(const std::string& file, int usernameIndex, const std::string& username);
// Date range check
bool isDateInRange(const std::string& target, const std::string& from, const std::string& to);

#endif
