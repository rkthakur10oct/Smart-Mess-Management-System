// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// Student dashboard entry point
void studentDashboard(const std::string& username);

// Core student features
void viewStudentProfile(const std::string& username);
void viewAttendance(const std::string& username);
void submitFeedback(const std::string& username);
void resetStudentPassword(const std::string& username);
void viewOwnFeedback(const std::string& username, const std::string& role);
void manageOwnFeedback(const std::string& username, const std::string& role);
// Meal booking
void preBookMeals(const std::string& username);         // Pre-book weekly meals
void viewMealBookingStatus(const std::string& username); // Optional: see booked meals
// Optional admin-side features
void markStudentAttendance();                // Staff/admin marks attendance
void viewAllStudentAttendance();             // Admin reporting

#endif
