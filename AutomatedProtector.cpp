#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

// Global Password
const string MASTER_PASSWORD = "secure123";

// Function to set text color
void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Function to initialize the console window
void initializeConsole() {
    SetConsoleTitle("File Protector: Made with Love to Protect Your Files");
}

// Function to print the header with colors
void displayHeader() {
    setColor(9, 0); // Blue text, black background
    cout << "====================================================\n";
    cout << "        Made with Love to Protect Your Files        \n";
    cout << "====================================================\n";
    setColor(7, 0); // Reset to default color
}

// Function to display a progress bar
void showProgressBar(int duration) {
    cout << "[";
    for (int i = 0; i < 20; ++i) {
        this_thread::sleep_for(chrono::milliseconds(duration / 20));
        cout << "#";
        cout.flush();
    }
    cout << "] Completed!\n";
}

// Function to log actions
void logAction(const string& action, const string& filePath) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << action << " - " << filePath << " at " << __TIME__ << " on " << __DATE__ << "\n";
        logFile.close();
    }
}

// Function to authenticate the user
bool authenticateUser() {
    string password;
    setColor(6, 0); // Yellow text
    cout << "Enter password to proceed: ";
    setColor(7, 0); // Reset to default color
    cin >> password;
    return password == MASTER_PASSWORD;
}

// Function to validate file or folder existence
bool validatePath(const string& path) {
    DWORD fileAttr = GetFileAttributes(path.c_str());
    return fileAttr != INVALID_FILE_ATTRIBUTES;
}

// Function to hide files or folders
void hideFileOrFolder(const string& path) {
    if (validatePath(path)) {
        showProgressBar(1000);
        if (SetFileAttributes(path.c_str(), FILE_ATTRIBUTE_HIDDEN)) {
            setColor(2, 0); // Green text
            cout << "[Success] The file/folder \"" << path << "\" is now hidden.\n";
            setColor(7, 0); // Reset to default color
            logAction("Hid", path);
        } else {
            setColor(4, 0); // Red text
            cout << "[Error] Unable to hide \"" << path << "\". Check permissions.\n";
            setColor(7, 0); // Reset to default color
        }
    } else {
        setColor(4, 0); // Red text
        cout << "[Error] The file/folder \"" << path << "\" does not exist.\n";
        setColor(7, 0); // Reset to default color
    }
}

// Function to unhide files or folders
void unhideFileOrFolder(const string& path) {
    if (validatePath(path)) {
        showProgressBar(1000);
        if (SetFileAttributes(path.c_str(), FILE_ATTRIBUTE_NORMAL)) {
            setColor(2, 0); // Green text
            cout << "[Success] The file/folder \"" << path << "\" is now visible.\n";
            setColor(7, 0); // Reset to default color
            logAction("Unhid", path);
        } else {
            setColor(4, 0); // Red text
            cout << "[Error] Unable to unhide \"" << path << "\". Check permissions.\n";
            setColor(7, 0); // Reset to default color
        }
    } else {
        setColor(4, 0); // Red text
        cout << "[Error] The file/folder \"" << path << "\" does not exist.\n";
        setColor(7, 0); // Reset to default color
    }
}

// Function to display a crying child ASCII art
void displayCryingChild() {
    setColor(4, 0); // Red text
    cout << "\n\n";
    cout << "       .-'''-.      \n";
    cout << "      /       \\    \n";
    cout << "     |  .-. .-. |   \n";
    cout << "     |  | | | | |   \n";
    cout << "   _ |  | | | | |_  \n";
    cout << "  ( `|  \\_/ \\_/ |` )\n";
    cout << "   \\_     _      _/ \n";
    cout << "     `\"\"\"\" \"\"\"\"`   \n";
    cout << "   CRYING CHILD :(  \n";
    setColor(7, 0); // Reset to default color
}

// Function to display the main menu
void displayMenu() {
    setColor(14, 0); // Yellow text
    cout << "\nChoose an option:\n";
    cout << "1. Hide Files/Folders\n";
    cout << "2. Unhide Files/Folders\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    setColor(7, 0); // Reset to default color
}

int main() {
    initializeConsole();
    displayHeader();

    if (!authenticateUser()) {
        setColor(4, 0); // Red text
        cout << "[Error] Authentication failed. Exiting...\n";
        setColor(7, 0); // Reset to default color
        return 1;
    }

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting... Goodbye!\n";
            break;
        }

        // Process config file for paths
        ifstream configFile("config.txt");
        if (!configFile.is_open()) {
            setColor(4, 0); // Red text
            cout << "[Error] Could not open config.txt. Ensure it exists.\n";
            setColor(7, 0); // Reset to default color
            continue;
        }

        string path;
        while (getline(configFile, path)) {
            switch (choice) {
                case 1:
                    hideFileOrFolder(path);
                    break;
                case 2:
                    unhideFileOrFolder(path);
                    break;
                default:
                    setColor(4, 0); // Red text
                    cout << "[Error] Invalid choice. Please try again.\n";
                    setColor(7, 0); // Reset to default color
            }
        }
        configFile.close();
    }

    return 0;
}
