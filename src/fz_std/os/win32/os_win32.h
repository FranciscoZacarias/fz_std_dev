#ifndef OS_CORE_WIN32_H
#define OS_CORE_WIN32_H

#pragma warning(push)
#pragma warning(disable: 4042) // Avoids known warning from winnls.h
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(pop)

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "advapi32")

///////////////////////////////////////////////////////
// @Section: Strings
function wchar_t* wchar_from_string8(String8 path);                /* Converts string8 to wide char array (16bit cstring) */
function String8  string8_from_wchar(Arena* arena, wchar_t* wstr); /* Converts a wide char array to a String */

///////////////////////////////////////////////////////
// @Section: Error handling
function LONG WINAPI win32_exception_filter(EXCEPTION_POINTERS* exception_ptrs); /* Win32 exception filer for SetUnhandledExceptionFilter */
function void _win32_output_last_error(DWORD error);
#define win32_check_error() Statement(DWORD e = GetLastError(); if (e != 0) { _win32_output_last_error(e); })

///////////////////////////////////////////////////////
// @Section: Modern Windows SDK functions
// rfj: We must dynamically link to them, since they can be missing in older SDKs
typedef HRESULT W32_SetThreadDescription_Type(HANDLE hThread, PCWSTR lpThreadDescription);
global W32_SetThreadDescription_Type *w32_SetThreadDescription_func = 0;

///////////////////////////////////////////////////////
// @Section: Extern
extern int    __argc;
extern char** __argv;

///////////////////////////////////////////////////////
// @Section: Win32 Globals
global HINSTANCE _hInstance            = NULL;
global WPARAM    _ApplicationReturn    = 0;

global LARGE_INTEGER win32_performance_frequency;

#endif // OS_CORE_WIN32_H