// report.h
#ifndef REPORT_H
#define REPORT_H

// Entry point for admin to access reporting tools
void reportPanel();

// Report generators
void generateAttendanceReport();     // View student/staff attendance
void generateFinanceReport();        // View income, expenses, profit/loss
void generateFeedbackReport();       // View pending/seen feedback
void exportReportsToCSV();           // Optional: save report summary as .csv
void generateMonthlyBillReport();    // Optional: student-wise mess dues
void generateMealBookingReport();    // Optional: weekly pre-booking summary
void generateGuestVisitReport();     // Optional: guest meal slot summary

#endif
