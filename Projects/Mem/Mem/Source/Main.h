#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define BREAK __debugbreak

void OptionalBreak();
#define OPT_BREAK OptionalBreak();

#define EXPERIMENTAL_MODE 0
