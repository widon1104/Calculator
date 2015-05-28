#include <execinfo.h>
#include <cstdlib>
#include "exception.h"

const char *Exception::what() const throw()
{
    return message_.c_str();
}

const char * Exception::StackTrace() const throw()
{
    return stackTrace_.c_str();
}

void Exception::FillStackTrace()
{
    return;
    //only work for linux
    const int len = 256;
    void *buffer[len];
    int nptrs = ::backtrace(buffer, len);
    char **strings = ::backtrace_symbols(buffer, nptrs);
    if (strings) {
        for (int i = 0; i < nptrs; i++) {
            stackTrace_.append(strings[i]);
            stackTrace_.push_back('\n');
        }
        free(strings);
    }
}
