#ifndef OS_INCLUDE_H
#define OS_INCLUDE_H

#include "os/core/os_core.h"
#if OS_WINDOWS
# include "os/core/win32/os_core_win32.h"
#elif OS_LINUX
# include "os/core/linux/os_core_linux.h"
#else
# error OS core layer not implemented for this operating system.
#endif

#endif // OS_INCLUDE_H