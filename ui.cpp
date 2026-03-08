#include "ui.h"
#include <iostream>
#include <stack>
#include <cstdlib>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

using namespace std;

// Screen navigation history
static stack<string> backStack;
static stack<string> forwardStack;
static string currentScreen = "Main";

// Clears the screen (cross-platform)
void clearScreen() {
    system(CLEAR_COMMAND);
}

// Pauses until user presses Enter
void pauseAndContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Displays a formatted header with title
void printHeader(const string& title) {
    clearScreen();
    cout << "====================================\n";
    cout << "     " << title << "\n";
    cout << "====================================\n";
}

// Prints a section title (inline)
void printMenuTitle(const string& section) {
    cout << "\n--- " << section << " ---\n";
}

// Prints a visual divider line
void printDivider() {
    cout << "------------------------------------\n";
}

// Ask user to retry or go back
bool confirmRetryOrBack() {
    int choice;
    cout << "\n1. Retry\n2. Back\nChoose option: ";
    cin >> choice;
    return (choice == 1);
}

// Push current screen to history and set new screen
void pushScreen(const string& screenName) {
    if (!currentScreen.empty()) backStack.push(currentScreen);
    currentScreen = screenName;
    while (!forwardStack.empty()) forwardStack.pop();  // Clear forward history
}

// Go back to previous screen
string popBack() {
    if (!backStack.empty()) {
        forwardStack.push(currentScreen);
        currentScreen = backStack.top();
        backStack.pop();
    }
    return currentScreen;
}

// Go forward to next screen (if available)
string popForward() {
    if (!forwardStack.empty()) {
        backStack.push(currentScreen);
        currentScreen = forwardStack.top();
        forwardStack.pop();
    }
    return currentScreen;
}

// Can go back?
bool canGoBack() {
    return !backStack.empty();
}

// Can go forward?
bool canGoForward() {
    return !forwardStack.empty();
}
