#ifndef OS_WIN32_WINDOW_H
#define OS_WIN32_WINDOW_H

///////////////////////////////////////////////////////
// @Section: Window
typedef struct OS_Window_Win32
{
  OS_Window state;
  HWND window_handle;
  HDC  device_context;
} OS_Window_Win32;

global OS_Window_Win32 g_os_window_win32;

///////////////////////////////////////////////////////
// @Section: Window
function HWND _win32_window_create(HINSTANCE hInstance, s32 width, s32 height); /* Creates a win32 window */
function void _win32_window_resize_callback(s32 width, s32 height);             /* Resize window callback */

#endif // OS_WIN32_WINDOW_H