#include <iostream>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>
#include "auth.cpp"

using namespace std;

namespace fs = std::filesystem;

void displayProgress(const string& message) {
    cout << "\033[36m[Processing]\033[0m " << message << " ";
    for (int i = 0; i < 10; ++i) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(200)); // Simulate delay
    }
    cout << " \033[32m[Done]\033[0m\n";
}

void logAction(const string& action, const string& filePath) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << action << " - " << filePath << " at " << __TIME__ << " on " << __DATE__ << "\n";
        logFile.close();
    }
}

void recoverAllLostFiles(const string& directory) {
    cout<<"\n";
    cout << "\033[36m==================================\033[0m\n";
    cout << "        Recovering Files Program        \n";
    cout << "\033[36m==================================\033[0m\n";
    cout<<"\n";

    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            const auto& path = entry.path().string();
            DWORD attributes = GetFileAttributes(path.c_str());
            if (attributes & FILE_ATTRIBUTE_HIDDEN) {
                displayProgress("Recovering your files .......... ");
                if (SetFileAttributes(path.c_str(), attributes & ~FILE_ATTRIBUTE_HIDDEN)) {
                    cout << "\033[32m[Success]\033[0m Your files are recovered successfully!\n";
                    logAction("Recover", path);
                } else {
                    cout << "\033[31m[Error]\033[0m Unable to recover your files.\n";
                }
            }
        }
    } catch (const exception& e) {
        cout << "\033[31m[Exception]\033[0m " << e.what() << "\n";
    }
    cout << "\033[36m==================================\033[0m\n";
}

int main() {
    ifstream configFile("configUnhide.txt");
    string directory;

    if (configFile.is_open() && getline(configFile, directory)) {
        recoverAllLostFiles(directory);
    } else {
        cout << "\033[31m[Error]\033[0m Failed to get your files. Please try.\n";
    }
    return 0;
}
