#include "common.h"

/**
 * Windows
 */
// void getCurrentTime(tm* tm)
// {
//     std::time_t now = std::time(0);
//     localtime_s(tm, &now);
// }

/**
 * Linux
 */
void getCurrentTime(tm* tm)
{
    std::time_t now = std::time(0);
    localtime_r(&now, tm);
}