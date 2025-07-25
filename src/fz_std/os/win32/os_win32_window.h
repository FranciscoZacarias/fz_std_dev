#ifndef OS_WIN32_WINDOW_H
#define OS_WIN32_WINDOW_H

///////////////////////////////////////////////////////
// @Section: Window

function HWND _win32_window_create(HINSTANCE hInstance, s32 width, s32 height); /* Creates a win32 window */
function void _win32_window_resize_callback(s32 width, s32 height);   /* Resize window callback */

#endif // OS_WIN32_WINDOW_H