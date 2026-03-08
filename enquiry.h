// enquiry.h
#ifndef ENQUIRY_H
#define ENQUIRY_H

#include <string>

// Student/Staff/Guest submits enquiry to admin
void submitEnquiry(const std::string& username, const std::string& role);

// Admin views all enquiries
void viewEnquiries();

// Admin responds to enquiries (status update)
void respondToEnquiries();

#endif
