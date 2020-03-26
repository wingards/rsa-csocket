#include "error_functions.h"


static void error_dealer(int errnoflag, int level, const char *format, va_list ap){

    const int MAXSIZE = 256;
    int errno_save,n;
    char buf[MAXSIZE +1];

    errno_save = errno;
    int daemon_proc = 1;

#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXSIZE, format, ap);
#else
    vsprintf(buf, format, ap);
#endif

    if(daemon_proc){
        n = strlen(buf);
        if (errnoflag)
            snprintf(buf + n, MAXSIZE - n, ": %s\n", strerror(errno_save));
            syslog(level, "%s" ,buf);
    }else{
        fflush(stdout);
        //if(level == LOG_LEVEL_ERROR)
            //log_info("%s", buf);
        //else
            //log_error("%s", buf);
        fflush(stderr);
    }
    return ;
}

void fatal_user_exit(const char *format, ...){

    va_list ap;
    va_start(ap, format);
    error_dealer(1, LOG_LEVEL_ALERT, format, ap);
    va_end(ap);
    exit(1);

}

void fatal_sys_exit(const char *format, ...){
    va_list ap;
    va_start(ap, format);
    error_dealer(0, LOG_LEVEL_ALERT, format, ap);
    va_end(ap);
    exit(1);

}
