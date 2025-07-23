
///////////////////////////////////////////////////////
// @Section: Win32 Globals
global HDC       _DeviceContextHandle  = null;
global HWND      _WindowHandle         = null;
global HINSTANCE _hInstance            = null;

global b32 _IsOpenGLContextEnabled = false;
global b32 _IsTerminalEnabled      = false;
global b32 _IsWindowEnabled        = false;

global Vec2S32 _WindowDimensions = {0};

///////////////////////////////////////////////////////
// @Section: Window

function void _win32_window_resize_callback(s32 width, s32 height); /* Resize window callback */

///////////////////////////////////////////////////////
// @Section: Error handling

function LONG WINAPI win32_exception_filter(EXCEPTION_POINTERS* exception_ptrs); /* Win32 exception filer for SetUnhandledExceptionFilter */

///////////////////////////////////////////////////////
// @Section: Modern Windows SDK functions
// rfj: We must dynamically link to them, since they can be missing in older SDKs

typedef HRESULT W32_SetThreadDescription_Type(HANDLE hThread, PCWSTR lpThreadDescription);
global W32_SetThreadDescription_Type *w32_SetThreadDescription_func = 0;