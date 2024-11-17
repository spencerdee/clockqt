#include "common.h"

/**
 * Windows
 */
#ifdef _WIN32
void getCurrentTime(tm* tm)
{
    std::time_t now = std::time(0);
    localtime_s(tm, &now);
}
#endif

/**
 * Linux
 */
#ifdef __linux__
void getCurrentTime(tm* tm)
{
    std::time_t now = std::time(0);
    localtime_r(&now, tm);
}
#endif