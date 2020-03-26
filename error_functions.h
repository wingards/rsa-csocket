#define __USE_BSD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>

const int LOG_LEVEL_PANIC = 0;
const int LOG_LEVEL_ALERT = 1;
const int LOG_LEVEL_ERROR = 3;
const int LOG_LEVEL_WARN  = 4;
const int LOG_LEVEL_DEBUG = 7;

static void error_dealer(int errnoflag, int level, const char *format, va_list ap);

void fatal_user_exit(const char *format, ...);

void fatal_sys_exit(const char *format, ...);
