#ifndef _FileUtils_H_
#define _FileUtils_H_

#include <string>
#include <vector>

#define _Win32
#ifdef _Win32

std::vector<std::string> ReadDir(const char* directory);

#else
// MAC
// Linux
// Android
#endif // _Win32

int CharToInt(char num);
void WriteRawBytesToFile(const char* filename, const char* data, int numBytes);

char* ReadRawBytesFromFile(const char* filename);
bool FileExists(const char* filename);
char* LoadFile(const char* filename);
char* LoadCompleteFile(const char* filename, long* length);

#endif // _FileUtils_H_