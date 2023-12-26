#include "Graphics\SetupGraphics.h"

#include <Windows.h>
#include <iostream>

void OutputMessage(const char* message, ...)
{
#define MAX_MESSAGE 1024
    char buffer[MAX_MESSAGE];
    va_list arg;
    va_start(arg, message);
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, message, arg);
    va_end(arg);

    buffer[MAX_MESSAGE - 1] = 0; // vsnprintf_s might do this, but docs are unclear
    OutputDebugStringA(buffer);
}

void ConsolePrint(int error, const char* description)
{
    // fprintf(stderr, "Error %d: %s\n", error, description);
    std::cout << description << std::endl;
}