#pragma once

struct CodeInfo
{
    CodeInfo(const char* oFunction, const char* oFile, const char* oLine)
    {
        function = oFunction;
        file = oFile;
        line = oLine;
    }

    const char* function = nullptr;
    const char* file = nullptr;
    const char* line = nullptr;
};

#define Info_Macro() CodeInfo(__FUNCTION__, __FILE__, __LINE__)