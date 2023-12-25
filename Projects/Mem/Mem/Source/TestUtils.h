#ifndef _TestUtils_H_
#define _TestUtils_H_

double MyGetSystemTime();

void OutputPrint(const char* message, ...);
void ConsolePrint(const char* string, ...);

void StartTest();
double EndTest();

#endif //!_TestUtils_H_