// createlongpathtextfile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>

#define BUFSIZE 4096

int main()
{
    using namespace std;

    string longPath{ 0 };

    cout << "Please enter a long full path name in the UNC format. E.g. \\\\?\\C:\\Temp\\verylongfilename.txt):\n";
    getline(std::cin, longPath);

    //cout << "\nYou've entered:\n";
    //cout << longPath;

    //TODO: Bug on creating file within solution folder instead of intended target location
    HANDLE fileHandle = CreateFileW((LPCWCHAR)longPath.c_str(), GENERIC_WRITE, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
     if (INVALID_HANDLE_VALUE == fileHandle)
    {
        cerr << "\n\nFailed to create file!" << endl;
        return 1;
    }

     DWORD dwRetVal{ 0 };
     
     TCHAR Path[BUFSIZE];
     dwRetVal = GetFinalPathNameByHandleW(fileHandle, Path, BUFSIZE, VOLUME_NAME_NT);
     if (dwRetVal < BUFSIZE)
     {
         _tprintf(TEXT("\nThe final path is: \n%s\n"), Path);
     }

    /*string text = "Hello World!";
    DWORD bytesWritten{ 0 };
    if (!WriteFile(fileHandle, text.c_str(), text.length(), &bytesWritten, NULL))
    {
        cerr << "Failed to write to file..." << endl;
        return 1;
    }*/

    CloseHandle(fileHandle);

    cout << "\n\nFile created successfully!" << endl;
    return 0;
}
