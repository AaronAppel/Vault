#ifndef _Program_Args_H_
#define _Program_Args_H_

bool ArgumentExists(int argc, char** argv, const char* argumentString);
std::map<const char*, const char*> ArgumentKeyValuePairs(int argc, char** argv);

#endif // !_Program_Args_H_