// guest.h
#ifndef GUEST_H
#define GUEST_H

#include <string>

// Guest main dashboard
void guestMenu(const std::string& guestId);

// Guest registration & login
void guestRegister();       // Independent registration
void guestLogin();          // Login and redirect to guestMenu

void guestDashboard(const std::string& username);

// Guest features
void viewGuestProfile(const std::string& guestId);
void viewWeeklyMenu();
void downloadGuestReceipt(const std::string& guestId);
void submitFeedback(const std::string& guestId, const std::string& role);
void submitEnquiry(const std::string& guestId, const std::string& role);
void viewOwnFeedback(const std::string& guestId, const std::string& role);
void manageOwnFeedback(const std::string& username, const std::string& role);
// Admin controls (optional extensions)
void viewAllGuestBookings();            // Admin can see all guest bookings
void blacklistGuest(const std::string& guestId);  // Optional: Block guest from booking again
bool isGuestBlacklisted(const std::string& guestId);

#endif
