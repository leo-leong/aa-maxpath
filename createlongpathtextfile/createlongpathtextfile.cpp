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
    size_t size{ 0 };
    size_t requiredSize{ 0 };
    wchar_t* pwc;

    cout << "Please enter a long full path name in the UNC format. E.g. \\\\?\\C:\\Temp\\verylongfilename.txt):\n";
    getline(std::cin, longPath);

    auto cstr = longPath.c_str();
    requiredSize = strlen(cstr)+1;
    pwc = new wchar_t[requiredSize];
    mbstowcs_s(&size, pwc, requiredSize, cstr, requiredSize - 1);

    //TODO: Bug on creating file within solution folder instead of intended target location
     HANDLE fileHandle = CreateFileW(pwc, GENERIC_WRITE, NULL, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
     if (INVALID_HANDLE_VALUE == fileHandle)
    {
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();

		FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

        _tprintf(TEXT("\n\nFailed to create file with error:\n\n\t%s"), (LPTSTR)lpMsgBuf);

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
