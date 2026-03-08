// staff.h
#ifndef STAFF_H
#define STAFF_H

#include <string>

// Staff dashboard entry point
void staffDashboard(const std::string& username);

// Staff operations
void viewStaffProfile(const std::string& username);
void viewStaffAttendance(const std::string& username);
void viewSalaryStatus(const std::string& username);
void submitStaffFeedback(const std::string& username);
void resetStaffPassword(const std::string& username);
void viewOwnFeedback(const std::string& username, const std::string& role);
void manageOwnFeedback(const std::string& username, const std::string& role);
// Optional admin-side features
void markStaffAttendance();                // Admin/staff marks attendance
void viewAllStaffAttendance();             // Admin views all staff records
void exportStaffAttendanceReport();        // Optional: CSV or PDF

#endif
