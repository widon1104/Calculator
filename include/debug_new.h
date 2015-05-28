#ifndef DEBUG_NEW
#define DEBUG_NEW

#include "tracer.h"

#ifndef NDEBUG
#define new new(__FILE__, __LINE__)
#endif

#endif // DEBUG_NEW

