// feedback.h
#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

// Student/Staff/Guest submits feedback
void submitFeedback(const std::string& username, const std::string& role);

// Admin views all feedbacks
void viewAllFeedback();

// Admin responds to feedback (mark as Seen)
void respondToFeedback();

#endif
