#ifndef STUB_GLIBC_H_
#define STUB_GLIBC_H_

#include <stdio.h>
#include <stdarg.h>

void enable_printf();
void disable_printf();

extern "C" int stub_printf(const char *fmt, ...);//重载printf

#undef printf
#define printf stub_printf


#endif /* STUB_GLIBC_H_ */
