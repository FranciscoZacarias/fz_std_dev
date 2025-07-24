#ifndef OS_CORE_WIN32_H
#define OS_CORE_WIN32_H

#pragma warning(push)
#pragma warning(disable: 4042) // Avoids known warning from winnls.h
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#pragma warning(pop)

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "advapi32")

///////////////////////////////////////////////////////
// @Section: Extern

extern int __argc;
extern char ** __argv;

///////////////////////////////////////////////////////
// @Section: Win32 Globals
global HDC       _DeviceContextHandle  = null;
global HWND      _WindowHandle         = null;
global HINSTANCE _hInstance            = null;

global b32 _IsOpenGLContextEnabled = false;
global b32 _IsTerminalEnabled      = false;


global LARGE_INTEGER os_performance_frequency;

///////////////////////////////////////////////////////
// @Section: Strings

function wchar_t* wchar_from_string8(String8 path); /* Converts string8 to wide char array (16bit cstring) */


///////////////////////////////////////////////////////
// @Section: Window

function HWND _win32_window_create(HINSTANCE hInstance, s32 width, s32 height); /* Creates a win32 window */
function void _win32_window_resize_callback(s32 width, s32 height);   /* Resize window callback */

///////////////////////////////////////////////////////
// @Section: Error handling

function LONG WINAPI win32_exception_filter(EXCEPTION_POINTERS* exception_ptrs); /* Win32 exception filer for SetUnhandledExceptionFilter */

///////////////////////////////////////////////////////
// @Section: Modern Windows SDK functions
// rfj: We must dynamically link to them, since they can be missing in older SDKs

typedef HRESULT W32_SetThreadDescription_Type(HANDLE hThread, PCWSTR lpThreadDescription);
global W32_SetThreadDescription_Type *w32_SetThreadDescription_func = 0;

#endif // OS_CORE_WIN32_H