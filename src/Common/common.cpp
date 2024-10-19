#include "common.h"

void getCurrentTime(tm* tm)
{
    std::time_t now = std::time(0);
    localtime_s(tm, &now);
}