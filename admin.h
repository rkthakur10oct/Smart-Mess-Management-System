// admin.h
#ifndef ADMIN_H
#define ADMIN_H

// Admin core functions
void adminDashboard();
void adminLogin();
void updateAdminProfile();
void resetUserCredentials();
void markAttendancePanel();
void viewAttendanceSummary();

// Registration functions
void registerStudent();
void registerStaff();
void registerGuestByAdmin();  // ✅ Added this missing function

// Viewing all users
void viewAllStudents();
void viewAllStaff();
void viewAllGuests();

// Mess and management functions
void editWeeklyMenu();
void manageHolidays();
void viewAuditLog();
void broadcastMessage();
void viewNotifications();
void viewFeedbacks();
void viewEnquiries();

#endif
