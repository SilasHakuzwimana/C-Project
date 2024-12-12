#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include "auth.cpp"

using namespace std;

// Function to set text color
void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Function to initialize the console window
void initializeConsole() {
    SetConsoleTitle("File Protector");
}

// Function to print the header with colors
// Function to print the header with colors
void displayHeader() {
    cout<<"\n";
    setColor(9, 0); // Blue text, black background
    cout << "====================================================\n";
    cout << "        Made with Love to Protect Your Files        \n";
    cout << "====================================================\n";
    setColor(7, 0); // Reset to default color
    cout<<"\n";
}

// Function to display a crying child ASCII art when files are lost
void displayCryingChild() {
    setColor(4, 0); // Red text, black background
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

// Function to display a progress message
void displayProgress(const string& message) {
    setColor(6, 0); // Yellow text, black background
    cout << "[Processing] " << message;
    for (int i = 0; i < 10; ++i) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(200)); // Simulate delay
    }
    cout << " [Done]\n";
    setColor(7, 0); // Reset to default color
}

// Function to log action to file
void logAction(const string& action, const string& filePath) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << action << " - " << filePath << " at " << __TIME__ << " on " << __DATE__ << "\n";
        logFile.close();
    }
}

// Function to hide files or folders
void hideFileOrFolder(const string& path) {
    displayProgress("Protecting your files...");
    if (SetFileAttributes(path.c_str(), FILE_ATTRIBUTE_HIDDEN)) {
        setColor(2, 0); // Green text, black background
        cout << "[Success] Your files/folders are now lost and there're no longer visible.\n";
        setColor(7, 0); // Reset to default color
        logAction("Hid", path);
    } else {
        setColor(4, 0); // Red text, black background
        cout << "[Error] Unable to protect your files. Please check the path and permissions and try again.\n";
        setColor(7, 0); // Reset to default color
    }
}

// Function to recommend unhide action with a crying child
void recommendUnhideAction() {
    setColor(14, 0); // Yellow text, black background
    cout << "[Warning] Your files have been lost and are no longer visible!\n";
    displayCryingChild(); // Display crying child ASCII art
    
    cout << "\nTo recover your files, run the recovery program by clicking  below:\n\n";
    setColor(2, 0); // Green text, black background
    cout<<"\n";
     // Simulate clickable link to unhide files
    std::cout << "\033[36m[Follow instruction below to Recover Files]\033[0m\n";
    cout<<"\n";
    std::cout << "\033[1;32mPress 'R' and Enter to recover hidden files.\033[0m\n";

    // Wait for user to press 'R'
    char input;
    std::cin >> input;

    if (input == 'R' || input == 'r' and authenticateUser()) {
            std::string command = "recovery.exe"; // Ensure recovery.exe exists in the same directory
            system(command.c_str());
            std::cout << "\033[1;32mRecovery tool has been executed!\033[0m\n";
        } else {
            std::cout << "\033[31mAuthentication failed.\n Recovery tool not executed.\033[0m\n";
        }
    }

int main() {
    // Initialize the console window
    initializeConsole();

    // Display header
    displayHeader();

    // Read path from config file
    ifstream configFile("config.txt");
    string path;
    if (configFile.is_open() && getline(configFile, path)) {
        hideFileOrFolder(path);
        recommendUnhideAction();
    } else {
        setColor(4, 0); // Red text, black background
        cout << "[Error] Failed to read files. Please try again.\n";
        setColor(7, 0); // Reset to default color
    }

    // End console session
    cout << "\nPress any key to exit...\n";
    cin.get();
    return 0;
}
