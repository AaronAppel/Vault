#include "Main.h"

#include <debugapi.h>
#include <iostream>
#include <profileapi.h>
#include <stdarg.h>

#include "TestUtils.h"

double lasttime = MyGetSystemTime();
double currtime = MyGetSystemTime();
float deltatime = (float)(currtime - lasttime);

double MyGetSystemTime()
{
	unsigned __int64 freq;
	unsigned __int64 time;

	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&time);

	double timeseconds = (double)time / freq;

	return timeseconds;
}

void OutputPrint(const char* message, ...)
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

void ConsolePrint(const char* string, ...)
{
#define MAX_MESSAGE 1024
	char buffer[MAX_MESSAGE];
	va_list arg;
	va_start(arg, string);
	vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, string, arg);
	va_end(arg);

	buffer[MAX_MESSAGE - 1] = 0; // vsnprintf_s might do this, but docs are unclear
	std::cout << buffer << std::endl;
}

void StartTest()
{
	currtime = MyGetSystemTime();
	deltatime = (float)(currtime - lasttime);
	lasttime = currtime;
}

double EndTest()
{
	currtime = MyGetSystemTime();
	deltatime = (float)(currtime - lasttime);
	lasttime = currtime;

	std::cout << "ms: " << deltatime * 1000 << std::endl;
	return deltatime;
}