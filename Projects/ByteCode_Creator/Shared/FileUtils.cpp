#include "Graphics\SetupGraphics.h"

#include <fstream>
#include <iostream>
#include <string>


#define _Win32 // TODO: Fix multi platform

#ifdef _Win32
#include <windows.h>
#include <handleapi.h> // INVALID_HANDLE_VALUE
#include <vector>
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa364418(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa365740(v=vs.85).aspx
// https://stackoverflow.com/questions/26475540/c-having-problems-with-a-simple-example-of-findfirstfile

std::vector<std::string> ReadDir(const char* directory)
{
    // variables
    std::vector<std::string> fileList; // list of file names with extensions
    WIN32_FIND_DATA ffd; // file data object
    HANDLE hand = INVALID_HANDLE_VALUE; // file handle
    std::string dir = directory; // used for easy appending

    dir.append("*.*"); // append "search for all" instruction
    hand = FindFirstFile(dir.c_str(), &ffd); // get the first file in directory

    // valid directory?
    if (INVALID_HANDLE_VALUE == hand)
    {
        int bp = 1; // error
        return fileList;
    }

    // read directory
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // std::cout << ffd.cFileName << std::endl;
        }
        else
        {
            std::cout << ffd.cFileName << std::endl;
            fileList.push_back(ffd.cFileName);
        }
    } while (FindNextFile(hand, &ffd) != 0);

    DWORD dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        //DisplayErrorBox(TEXT("FindFirstFile"));
        int bp = 1;
    }

    FindClose(hand);
    return fileList;
}

#else
// MAC
// Linux
// Android
#endif // _Win32


int CharToInt(char num)
{
    return num - 49;
}

void WriteRawBytesToFile(const char* filename, const char* data, int numBytes)
{
    std::ofstream oStream;
    oStream.open(filename, std::ios_base::binary);
    if (oStream.is_open())
    {
        oStream.write((char*)data, numBytes);
        oStream.close();
    }
}

char* ReadRawBytesFromFile(const char* filename)
{
    std::ifstream iStream;
    iStream.open(filename, std::ios_base::binary);

    char* data = nullptr;
    if (iStream.is_open())
    {
        int size = 0;
        iStream.seekg(0, std::ios::end);
        size = (int)iStream.tellg();

        data = new char[size];
        iStream.read(data, size);
        iStream.close();
        return data;
    }

    return nullptr; // pass bytes back
}

// utility
bool FileExists(const char* filename)
{
    FILE* filehandle;
    errno_t error = fopen_s(&filehandle, filename, "r");
    if (filehandle)
        fclose(filehandle);

    return error == 0;
}

char* LoadFile(const char* filename)
{
    FILE* filehandle;
    errno_t error = fopen_s(&filehandle, filename, "r+");
    if (filehandle)
    {
        // find the length of the file
        fseek(filehandle, 0, SEEK_END); // go to the end
        long size = ftell(filehandle); // read the position in bytes
        rewind(filehandle); // go back to the beginning
                            // before we can read, we need to allocate a buffer of the right size
        char* buffer = new char[size];
        fread(buffer, size, 1, filehandle);
        fclose(filehandle);

        return buffer;
    }
    else
    {
        return NULL;
    }
}

char* LoadCompleteFile(const char* filename, long* length)
{
    char* filecontents = 0;

    FILE* filehandle;
    errno_t error = fopen_s(&filehandle, filename, "rb");

    if (filehandle)
    {
        fseek(filehandle, 0, SEEK_END);
        long size = ftell(filehandle);
        rewind(filehandle);

        filecontents = new char[size + 1];
        fread(filecontents, size, 1, filehandle);
        filecontents[size] = 0;

        if (length)
            *length = size;

        fclose(filehandle);
    }

    if (filecontents == 0)
    {
        OutputMessage("\nFileUtilities: LoadCompleteFile() encountered errors loading \"%s\"-> \n", filename);
        delete[] filecontents;
        filecontents = 0;
        if (error == 2)
        {
            OutputMessage("No such file or directory!");
        }
    }

    return filecontents;
}