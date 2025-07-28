#ifndef FZ_OPENGL_H
#define FZ_OPENGL_H

#ifndef FZ_WINDOW
# error fz_opengl.h requires including fz_window.h
#endif
#define FZ_OPENGL 1

#include "opengl\opengl.h"
#if OS_WINDOWS
# include "opengl\win32\win32_opengl.h"
#elif OS_LINUX
# error fz_opengl for linux os not implemented
#endif

#include "opengl\opengl.c"
#if OS_WINDOWS
# include "opengl\win32\win32_opengl.c"
#elif OS_LINUX
# error fz_opengl for linux os not implemented
#endif


#endif // FZ_OPENGL_H