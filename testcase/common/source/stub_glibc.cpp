#include "stub_glibc.h"

bool g_stub_printf = false;

void enable_printf()
{
    g_stub_printf = true;
}

void disable_printf()
{
    g_stub_printf = false;
}

int stub_printf(const char *fmt, ...)
{
    if (!g_stub_printf)
        return -1;

    va_list args;
    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);

    return ret;
}