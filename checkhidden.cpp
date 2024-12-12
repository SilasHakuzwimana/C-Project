#include <iostream>
#include <windows.h>

bool isHidden(const std::string& path) {
    DWORD attributes = GetFileAttributes(path.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        std::cout << "Error: Unable to retrieve attributes for \"" << path << "\".\n";
        return false; // Could not retrieve attributes
    }
    return (attributes & FILE_ATTRIBUTE_HIDDEN); // Check if hidden flag is set
}

int main() {
    std::string filePath;
    std::cout << "Enter the path of the file or folder: ";
    std::getline(std::cin, filePath);

    if (isHidden(filePath)) {
        std::cout << "The file/folder \"" << filePath << "\" is hidden.\n";
    } else {
        std::cout << "The file/folder \"" << filePath << "\" is not hidden.\n";
    }

    return 0;
}
