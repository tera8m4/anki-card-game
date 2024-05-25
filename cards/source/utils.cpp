#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#pragma execution_character_set( "utf-8" )
#endif

void utils::enableUTF8()
{
#ifdef _WIN32
    // Enable UTF-8 mode for the console
    SetConsoleOutputCP(CP_UTF8);
#endif
}
