#ifndef UI_H
#define UI_H

#include <string>

// UI Display Functions
void clearScreen();                                 // Clear console screen
void pauseAndContinue();                            // Wait for user input
void printHeader(const std::string& title);         // Print section header
void printMenuTitle(const std::string& section);    // Print inline menu section
void printDivider();                                // Print a divider line
bool confirmRetryOrBack();                          // Ask user: retry or back

// Navigation History Functions
void pushScreen(const std::string& screenName);     // Save current screen to back stack
std::string popBack();                              // Return to previous screen
std::string popForward();                           // Go forward if available
bool canGoBack();                                   // Check if back is possible
bool canGoForward();                                // Check if forward is possible

#endif
