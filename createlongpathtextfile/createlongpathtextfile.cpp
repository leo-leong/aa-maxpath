// createlongpathtextfile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    using namespace std;

    string longPath{ 0 };

    cout << "Please enter a long full path name in the UNC format. E.g. \\\\?\\C:\\Temp\\verylongfilename.txt):\n";
    getline(std::cin, longPath);

    cout << "\nYou've entered:\n";
    cout << longPath;

    HANDLE fileHandle = CreateFileW((LPCWCHAR)longPath.c_str(), GENERIC_WRITE, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
     if (INVALID_HANDLE_VALUE == fileHandle)
    {
        cerr << "\n\nFailed to create file!" << endl;
        return 1;
    }

    string text = "Hello World!";
    DWORD bytesWritten{ 0 };
    if (!WriteFile(fileHandle, text.c_str(), text.length(), &bytesWritten, NULL))
    {
        cerr << "Failed to write to file..." << endl;
        return 1;
    }

    CloseHandle(fileHandle);

    cout << "\n\nFile created successfully!" << endl;
    return 0;
}
