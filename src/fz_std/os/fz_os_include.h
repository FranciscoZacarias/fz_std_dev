#ifndef FZ_OS_INCLUDE_H
#define FZ_OS_INCLUDE_H

#include "os/core/os_core.h"

#ifndef FZ_STD_INCLUDED
# error fz_os_window.h requires including fz_std library. Please include fz_include.h before including this header.
#endif

#if OS_WINDOWS
# include "os/core/win32/os_core_win32.h"
#elif OS_LINUX
# include "os/core/linux/os_core_linux.h"
#else
# error OS core layer not implemented for this operating system.
#endif

#endif // FZ_OS_INCLUDE_H