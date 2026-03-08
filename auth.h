// auth.h
#ifndef AUTH_H
#define AUTH_H

#include <string>

// Admin Authentication
void adminRegister();                    // First-time admin registration
void adminLogin();                       // Admin login

// Student/Staff Login (Registered by Admin)
void studentLogin();                     // Student login
void staffLogin();                       // Staff login

// Guest Login/Registration (Admin + Independent)
void guestRegister();                    // Guest registration (independent or by admin)
void guestLogin();                       // Guest login
void guestAccess();  // Allows guest to choose register or login

// Credential Recovery System
void recoverPassword(const std::string& role);   // Recover password by role
void recoverUsername(const std::string& role);   // Recover username by role
bool verifySecretQA(const std::string& file, int unameIndex, const std::string& username); // internal Q/A check

#endif
