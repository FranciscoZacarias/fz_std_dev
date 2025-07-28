#ifndef FZ_WINDOW_H
#define FZ_WINDOW_H

#ifndef FZ_BASE
# error fz_window.h requires including fz_base.h
#endif
#define FZ_WINDOW 1

#include "os\os_window.h"
#if OS_WINDOWS
# include "os\win32\os_win32_window.h"
#elif OS_LINUX
# error fz_window for linux os not implemented
#endif

#include "os\os_window.c"
#if OS_WINDOWS
# include "os\win32\os_win32_window.c"
#elif OS_LINUX
# error fz_window for linux os not implemented
#endif


#endif // FZ_WINDOW_H