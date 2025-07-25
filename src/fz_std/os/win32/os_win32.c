
///////////////////////////////////////////////////////
// @Section: Strings
function wchar_t*
wchar_from_string8(String8 path)
{
  s32 len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)path.str, (s32)path.size, 0, 0);
  wchar_t *wstr = (wchar_t *)_alloca(sizeof(wchar_t) * (len + 1));
  MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)path.str, (s32)path.size, wstr, len);
  wstr[len] = 0;
  return wstr;
}

function String8
string8_from_wchar(Arena* arena, wchar_t* wstr)
{
  String8 result = {0};
  
  if (!wstr) {
    return result;
  }
  
  // Get required buffer size for UTF-8
  int required_size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
  if (required_size <= 0) {
    return result;
  }
  
  // Allocate from arena (subtract 1 to exclude null terminator from size)
  u8* buffer = array_push(arena, u8, required_size);
  if (!buffer) {
    return result;
  }
  
  // Convert to UTF-8
  int converted = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, (u8*)buffer, required_size, NULL, NULL);
  if (converted <= 0) {
    return result;
  }
  
  result.size = (u64)(converted - 1);
  result.str = buffer;
  
  return result;

}

///////////////////////////////////////////////////////
// @Section: System info
///////////////////////////////////////////////////////
// @Section: Process Info
///////////////////////////////////////////////////////
// @Section: Process Launch Parameters
///////////////////////////////////////////////////////
// @Section: Memory
function OS_Memory_Stats
os_memory_stats()
{
  OS_Memory_Stats result = {0};

  MEMORYSTATUSEX status = {0};
  status.dwLength = sizeof(status);

  if(GlobalMemoryStatusEx(&status))
  {
    result.total_physical     = (u64)status.ullTotalPhys;
    result.available_physical = (u64)status.ullAvailPhys;
    result.total_virtual      = (u64)status.ullTotalPageFile;
    result.used_virtual       = (u64)(status.ullTotalPageFile - status.ullAvailPageFile);
  }

  return result;
}

function void*
os_memory_reserve(u64 size)
{
  void *result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
  return result;
}

function b32
os_memory_commit(void *ptr, u64 size)
{
  b32 result = (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != 0);
  return result;
}

function void
os_memory_decommit(void *ptr, u64 size)
{
  VirtualFree(ptr, size, MEM_DECOMMIT);
}

function void
os_memory_release(void *ptr, u64 size)
{
  // NOTE(fz): Size not needed for windows. Though required for other OS's.
  VirtualFree(ptr, 0, MEM_RELEASE);
}

function u64
os_memory_get_page_size()
{
  SYSTEM_INFO info;
  GetSystemInfo(&info);
  u64 result = (u64)info.dwPageSize;
  return result;
}

///////////////////////////////////////////////////////
// @Section: Time
function void
os_timer_init()
{
  QueryPerformanceFrequency(&win32_performance_frequency);
  os_timer_start(&_Timer_ElapsedTime);
  os_timer_start(&_Timer_FrameTime);
}

function void
os_timer_start(Performance_Timer* timer)
{
  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  timer->start_ticks = (u64)counter.QuadPart;
  timer->end_ticks = 0;
  timer->elapsed_seconds = 0.0f;
}

function void
os_timer_end(Performance_Timer* timer)
{
  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  timer->end_ticks = (u64)counter.QuadPart;
  u64 delta = timer->end_ticks - timer->start_ticks;
  timer->elapsed_seconds = (f32)((f64)delta / (f64)win32_performance_frequency.QuadPart);
}

function f32
os_get_elapsed_time()
{
  LARGE_INTEGER current;
  QueryPerformanceCounter(&current);
  u64 delta = (u64)current.QuadPart - _Timer_ElapsedTime.start_ticks;
  return (f32)((f64)delta / (f64)win32_performance_frequency.QuadPart);
}

function f32
os_get_frame_time()
{
  LARGE_INTEGER current;
  QueryPerformanceCounter(&current);
  u64 delta = (u64)current.QuadPart - _Timer_FrameTime.start_ticks;
  return (f32)((f64)delta / (f64)win32_performance_frequency.QuadPart);
}

///////////////////////////////////////////////////////
// @Section: Console
function b32
os_console_init()
{
  b32 result = false;

  if (GetConsoleWindow() != NULL)
  {
    // Already attached to a console; no need to allocate a new one.
    result = false;
  }
  else if (AttachConsole(ATTACH_PARENT_PROCESS))
  {
    // Try attaching to parent process console.
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    result = true;
  }
  else if (AllocConsole())
  {
    // No console attached; allocate a new one.
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    result = true;
  }

  // Try to enable color
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (handle != INVALID_HANDLE_VALUE)
  {
    DWORD mode = 0;
    if (GetConsoleMode(handle, &mode))
    {
      if ((mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) == 0)
      {
        SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
      }
    }
  }

  return result;
}

function void
os_console_write(String8 string)
{

}

function void
os_console_write_line(String8 string)
{

}

function void
os_console_writef(char* fmt, ...)
{

}

function void
os_console_set_text_color(u8 r, u8 g, u8 b)
{

}

function void
os_console_reset_text_color()
{

}

function String8
os_console_read_line(Arena* arena)
{

}

function b32
os_console_has_input()
{

}

///////////////////////////////////////////////////////
// @Section: Files
function b32
os_file_create(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  HANDLE file = CreateFileW(wpath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  b32 result = (file != INVALID_HANDLE_VALUE);
  if(result)
  {
    CloseHandle(file);
  }
  return result;
}

function b32
os_file_delete(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  b32 result = DeleteFileW(wpath);
  return result;
}

function b32
os_file_exists(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  DWORD attr = GetFileAttributesW(wpath);
  b32 result = (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
  return result;
}

function u32
os_file_overwrite(String8 path, u8* data, u64 data_size)
{
  wchar_t *wpath = wchar_from_string8(path);
  HANDLE file = CreateFileW(wpath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if(file == INVALID_HANDLE_VALUE)
  {
    return 0;
  }
  DWORD written = 0;
  WriteFile(file, data, (DWORD)data_size, &written, 0);
  CloseHandle(file);
  return (u32)written;
}

function u32
os_file_append(String8 path, u8* data, u64 data_size)
{
  wchar_t *wpath = wchar_from_string8(path);
  HANDLE file = CreateFileW(wpath, FILE_APPEND_DATA, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if(file == INVALID_HANDLE_VALUE)
  {
    return 0;
  }
  SetFilePointer(file, 0, 0, FILE_END);
  DWORD written = 0;
  WriteFile(file, data, (DWORD)data_size, &written, 0);
  CloseHandle(file);
  return (u32)written;
}

function b32
os_file_wipe(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  HANDLE file = CreateFileW(wpath, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if(file == INVALID_HANDLE_VALUE)
  {
    return 0;
  }

  // Truncate by setting file pointer to start and calling SetEndOfFile
  SetFilePointer(file, 0, 0, FILE_BEGIN);
  b32 result = SetEndOfFile(file);
  CloseHandle(file);
  return result;
}

function u32
os_file_size(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  WIN32_FILE_ATTRIBUTE_DATA attr;
  if(!GetFileAttributesExW(wpath, GetFileExInfoStandard, &attr))
  {
    return 0;
  }
  ULARGE_INTEGER size;
  size.LowPart = attr.nFileSizeLow;
  size.HighPart = attr.nFileSizeHigh;
  return (u32)size.QuadPart;
}

function File_Data
os_file_load(Arena* arena, String8 path)
{
  File_Data result = {0};
  wchar_t *wpath = wchar_from_string8(path);
  HANDLE file = CreateFileW(wpath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if(file == INVALID_HANDLE_VALUE)
  {
    return result;
  }

  DWORD file_size = GetFileSize(file, 0);
  u8 *buffer = array_push(arena, u8, file_size);
  DWORD read = 0;
  if(ReadFile(file, buffer, file_size, &read, 0) && read == file_size)
  {
    result.path = path;
    result.data.str = buffer;
    result.data.size = file_size;
  }

  CloseHandle(file);
  return result;
}

function b32
os_file_has_extension(String8 filename, String8 ext)
{
  if(filename.size < ext.size + 1)
  {
    return 0;
  }

  String8 slice = string8_slice(filename, filename.size - ext.size, filename.size);
  b32 result = string8_match(slice, ext, true);
  return result;
}

function u64
os_file_get_last_modified_time(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  HANDLE file = CreateFileW(wpath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if(file == INVALID_HANDLE_VALUE)
  {
    return 0;
  }

  FILETIME ft;
  b32 success = GetFileTime(file, 0, 0, &ft);
  CloseHandle(file);

  if(!success)
  {
    return 0;
  }

  ULARGE_INTEGER time;
  time.LowPart  = ft.dwLowDateTime;
  time.HighPart = ft.dwHighDateTime;
  return time.QuadPart;
}

///////////////////////////////////////////////////////
// @Section: Directories
function b32      
os_directory_create(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  b32 result = CreateDirectoryW(wpath, 0);
  b32 exists = (GetLastError() == ERROR_ALREADY_EXISTS);
  return result || exists;
}

function b32  
os_directory_delete(String8 path)
{
  wchar_t *wpath = wchar_from_string8(path);
  b32 success = RemoveDirectoryW(wpath);
  return success;
}

function b32  
os_directory_move(String8 path, String8 destination)
{
  wchar_t *wsrc = wchar_from_string8(path);
  wchar_t *wdst = wchar_from_string8(destination);
  b32 success = MoveFileW(wsrc, wdst);
  return success;
}

function String8  
os_directory_pop(String8 path)
{
  String8 result = S("");
  for(u64 i = path.size; i > 0; i -= 1)
  {
    if(path.str[i - 1] == '/' || path.str[i - 1] == '\\')
    {
      result = string8_slice(path, 0, i - 1);
      break;
    }
  }
  return result;;
}

function String8  
os_directory_push(String8 path, String8 directory)
{
  Scratch scratch = scratch_begin(0, 0);
  b32 needs_slash = (path.size > 0 &&
                    path.str[path.size - 1] != '/' &&
                    path.str[path.size - 1] != '\\');

  String8 slash = S("/");
  String8 result;

  if(needs_slash)
  {
    String8 temp = string8_concat(scratch.arena, path, slash);
    result = string8_concat(scratch.arena, temp, directory);
  }
  else
  {
    result = string8_concat(scratch.arena, path, directory);
  }

  scratch_end(&scratch);
  return result;
}

///////////////////////////////////////////////////////
// @Section: Window Lifecycle
function void
os_window_open(s32 width, s32 height, String8 title)
{
  ShowWindow(_WindowHandle, SW_SHOW);
  UpdateWindow(_WindowHandle);
  os_window_set_size(width, height);
  os_window_set_title(title);
}

function void     
os_window_close()
{
  ShowWindow(_WindowHandle, SW_HIDE);
  UpdateWindow(_WindowHandle);
}

function b32
os_window_swap_buffers()
{
  b32 result = true;

  os_timer_end(&_Timer_FrameTime);
  os_timer_start(&_Timer_FrameTime);

  MSG msg = {0};
  if (_WindowHandle != null) {
    _input_update();
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) 
      {
        _ApplicationReturn = (s32)msg.wParam;
        result = false;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return result;
}

///////////////////////////////////////////////////////
// @Section: Window Flags

function b32
os_window_is_fullscreen()
{
  RECT rect;
  GetWindowRect(_WindowHandle, &rect);

  MONITORINFO mi = { sizeof(mi) };
  GetMonitorInfo(MonitorFromWindow(_WindowHandle, MONITOR_DEFAULTTONEAREST), &mi);

  b32 result = (rect.left   == mi.rcMonitor.left &&
                rect.top    == mi.rcMonitor.top &&
                rect.right  == mi.rcMonitor.right &&
                rect.bottom == mi.rcMonitor.bottom);

  return result;
}

function void
os_window_set_fullscreen(b32 set)
{
  static WINDOWPLACEMENT prev = { sizeof(prev) };
  if (set)
  {
    GetWindowPlacement(_WindowHandle, &prev);

    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(MonitorFromWindow(_WindowHandle, MONITOR_DEFAULTTONEAREST), &mi);

    SetWindowLong(_WindowHandle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowPos(_WindowHandle, HWND_TOP,
                 mi.rcMonitor.left, mi.rcMonitor.top,
                 mi.rcMonitor.right - mi.rcMonitor.left,
                 mi.rcMonitor.bottom - mi.rcMonitor.top,
                 SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
  }
  else
  {
    SetWindowLong(_WindowHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
    SetWindowPlacement(_WindowHandle, &prev);
    SetWindowPos(_WindowHandle, NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                 SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
  }
}

function b32
os_window_is_maximized()
{
  b32 result = IsZoomed(_WindowHandle);
  return result;
}

function void
os_window_set_maximized(b32 set)
{
  ShowWindow(_WindowHandle, set ? SW_MAXIMIZE : SW_RESTORE);
}

function b32
os_window_is_minimized()
{
  b32 result = IsIconic(_WindowHandle);
  return result;
}

function void
os_window_set_minimized(b32 set)
{
  ShowWindow(_WindowHandle, set ? SW_MINIMIZE : SW_RESTORE);
}

///////////////////////////////////////////////////////
// @Section: Window Appearance

function void
os_window_set_visible(b32 visible)
{
  ShowWindow(_WindowHandle, visible ? SW_SHOW : SW_HIDE);
}

function b32
os_window_set_title(String8 title)
{
  Scratch scratch = scratch_begin(0, 0);
  char* ctitle = cstring_from_string8(scratch.arena, title);
  b32 result = SetWindowTextA(_WindowHandle, ctitle);
  if (!result) 
  {
    win32_debug_output_last_error(S("CreateWindowExW"));
  }
  scratch_end(&scratch);
  return result;
}

function void
os_window_clear_custom_border_data()
{

}

function void
os_window_push_custom_title_bar(f32 thickness)
{

}

function void
os_window_push_custom_edges(f32 thickness)
{

}

function void
os_window_push_custom_title_bar_client_area(Range2F32 rect)
{

}

function void
os_window_set_position(Vec2F32 pos)
{
  SetWindowPos(_WindowHandle, 0,
               (int)pos.x, (int)pos.y, 0, 0,
               SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

function void
os_window_set_size(s32 width, s32 height)
{
  SetWindowPos(_WindowHandle, 0,
               0, 0, width, height,
               SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
}

///////////////////////////////////////////////////////
// @Section: Cursor
function void
os_cursor_set(Cursor_Type cursor)
{
  HCURSOR hCursor = NULL;

  switch (cursor)
  {
    case CURSOR_ARROW:
    {
      hCursor = LoadCursor(NULL, IDC_ARROW);
    }
    break;
    case CURSOR_HAND:
    {
      hCursor = LoadCursor(NULL, IDC_HAND);
    }
    break;
    case CURSOR_CROSSHAIR:
    {
      hCursor = LoadCursor(NULL, IDC_CROSS);
    }
    break;
    case CURSOR_IBEAM:
    {
      hCursor = LoadCursor(NULL, IDC_IBEAM);
    }
    break;
    case CURSOR_WAIT:
    { 
      hCursor = LoadCursor(NULL, IDC_WAIT);
    }
    break;
    case CURSOR_SIZE_ALL:
    {
      hCursor = LoadCursor(NULL, IDC_SIZEALL);
    }
    break;
    default:
    {
      hCursor = LoadCursor(NULL, IDC_ARROW);
    }
    break;
  }

  if (hCursor)
  {
    SetCursor(hCursor);
  }
}

function void
os_cursor_set_position(s32 x, s32 y)
{
  SetCursorPos(x, y);
}

function void
os_cursor_lock(b32 lock)
{
  if (lock)
  {
    RECT rect;
    GetClientRect(_WindowHandle, &rect);
    POINT center = {(rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2};
    ClientToScreen(_WindowHandle, &center);
    SetCursorPos(center.x, center.y);

    _IsCursorLocked      = true;
    _IgnoreNextMouseMove = true;

    // Reset deltas to avoid cursor jump
    _InputState.mouse_current.delta.x  = 0.0f;
    _InputState.mouse_current.delta.y  = 0.0f;
    _InputState.mouse_previous.delta.x = 0.0f;
    _InputState.mouse_previous.delta.y = 0.0f;
    MemoryCopyStruct(&_InputState.mouse_previous, &_InputState.mouse_current);
  }
  else
  {
    _IsCursorLocked = false;
  }
}

function void
os_cursor_hide(b32 hide)
{
  // Win32 quirk. It has an internal counter required to show the cursor.
  // The while loops just make sure it exhausts the counter and applies immediately.
  while (ShowCursor(hide ? FALSE : TRUE) >= 0 &&  hide);
  while (ShowCursor(hide ? FALSE : TRUE) < 0  && !hide);
}

///////////////////////////////////////////////////////
// @Section: Input-Keyboard

// Win32 VK code translation table - MUST match enum order exactly
static u32 _win32_key_table[Keyboard_Key_Count] =
{
  0x08, // Keyboard_Key_BACKSPACE
  0x0D, // Keyboard_Key_ENTER
  0x09, // Keyboard_Key_TAB
  0x10, // Keyboard_Key_SHIFT
  0x11, // Keyboard_Key_CONTROL
  0x13, // Keyboard_Key_PAUSE
  0x14, // Keyboard_Key_CAPS_LOCK
  0x1B, // Keyboard_Key_ESCAPE
  0x1C, // Keyboard_Key_CONVERT
  0x1D, // Keyboard_Key_NONCONVERT
  0x1E, // Keyboard_Key_ACCEPT
  0x1F, // Keyboard_Key_MODECHANGE
  0x20, // Keyboard_Key_SPACE
  0x21, // Keyboard_Key_PRIOR
  0x22, // Keyboard_Key_NEXT
  0x23, // Keyboard_Key_END
  0x24, // Keyboard_Key_HOME
  0x25, // Keyboard_Key_ARROW_LEFT
  0x26, // Keyboard_Key_ARROW_UP
  0x27, // Keyboard_Key_ARROW_RIGHT
  0x28, // Keyboard_Key_ARROW_DOWN
  0x29, // Keyboard_Key_SELECT
  0x2A, // Keyboard_Key_PRINT
  0x2B, // Keyboard_Key_EXECUTE
  0x2C, // Keyboard_Key_SNAPSHOT
  0x2D, // Keyboard_Key_INSERT
  0x2E, // Keyboard_Key_DELETE
  0x2F, // Keyboard_Key_HELP
  0x30, // Keyboard_Key_0
  0x31, // Keyboard_Key_1
  0x32, // Keyboard_Key_2
  0x33, // Keyboard_Key_3
  0x34, // Keyboard_Key_4
  0x35, // Keyboard_Key_5
  0x36, // Keyboard_Key_6
  0x37, // Keyboard_Key_7
  0x38, // Keyboard_Key_8
  0x39, // Keyboard_Key_9
  0x41, // Keyboard_Key_A
  0x42, // Keyboard_Key_B
  0x43, // Keyboard_Key_C
  0x44, // Keyboard_Key_D
  0x45, // Keyboard_Key_E
  0x46, // Keyboard_Key_F
  0x47, // Keyboard_Key_G
  0x48, // Keyboard_Key_H
  0x49, // Keyboard_Key_I
  0x4A, // Keyboard_Key_J
  0x4B, // Keyboard_Key_K
  0x4C, // Keyboard_Key_L
  0x4D, // Keyboard_Key_M
  0x4E, // Keyboard_Key_N
  0x4F, // Keyboard_Key_O
  0x50, // Keyboard_Key_P
  0x51, // Keyboard_Key_Q
  0x52, // Keyboard_Key_R
  0x53, // Keyboard_Key_S
  0x54, // Keyboard_Key_T
  0x55, // Keyboard_Key_U
  0x56, // Keyboard_Key_V
  0x57, // Keyboard_Key_W
  0x58, // Keyboard_Key_X
  0x59, // Keyboard_Key_Y
  0x5A, // Keyboard_Key_Z
  0x5B, // Keyboard_Key_LEFT_WIN
  0x5C, // Keyboard_Key_RIGHT_WIN
  0x5D, // Keyboard_Key_APPS
  0x5F, // Keyboard_Key_SLEEP
  0x60, // Keyboard_Key_NUMPAD0
  0x61, // Keyboard_Key_NUMPAD1
  0x62, // Keyboard_Key_NUMPAD2
  0x63, // Keyboard_Key_NUMPAD3
  0x64, // Keyboard_Key_NUMPAD4
  0x65, // Keyboard_Key_NUMPAD5
  0x66, // Keyboard_Key_NUMPAD6
  0x67, // Keyboard_Key_NUMPAD7
  0x68, // Keyboard_Key_NUMPAD8
  0x69, // Keyboard_Key_NUMPAD9
  0x6A, // Keyboard_Key_NUMPAD_MULTIPLY
  0x6B, // Keyboard_Key_NUMPAD_ADD
  0x6C, // Keyboard_Key_NUMPAD_SEPARATOR
  0x6D, // Keyboard_Key_NUMPAD_SUBTRACT
  0x6E, // Keyboard_Key_NUMPAD_DECIMAL
  0x6F, // Keyboard_Key_NUMPAD_DIVIDE
  0x70, // Keyboard_Key_F1
  0x71, // Keyboard_Key_F2
  0x72, // Keyboard_Key_F3
  0x73, // Keyboard_Key_F4
  0x74, // Keyboard_Key_F5
  0x75, // Keyboard_Key_F6
  0x76, // Keyboard_Key_F7
  0x77, // Keyboard_Key_F8
  0x78, // Keyboard_Key_F9
  0x79, // Keyboard_Key_F10
  0x7A, // Keyboard_Key_F11
  0x7B, // Keyboard_Key_F12
  0x7C, // Keyboard_Key_F13
  0x7D, // Keyboard_Key_F14
  0x7E, // Keyboard_Key_F15
  0x7F, // Keyboard_Key_F16
  0x80, // Keyboard_Key_F17
  0x81, // Keyboard_Key_F18
  0x82, // Keyboard_Key_F19
  0x83, // Keyboard_Key_F20
  0x84, // Keyboard_Key_F21
  0x85, // Keyboard_Key_F22
  0x86, // Keyboard_Key_F23
  0x87, // Keyboard_Key_F24
  0x90, // Keyboard_Key_NUMLOCK
  0x91, // Keyboard_Key_SCROLL
  0x92, // Keyboard_Key_NUMPAD_EQUAL
  0xA0, // Keyboard_Key_LEFT_SHIFT
  0xA1, // Keyboard_Key_RIGHT_SHIFT
  0xA2, // Keyboard_Key_LEFT_CONTROL
  0xA3, // Keyboard_Key_RIGHT_CONTROL
  0xA4, // Keyboard_Key_LEFT_MENU
  0xA5, // Keyboard_Key_RIGHT_MENU
  0xBA, // Keyboard_Key_SEMICOLON
  0xBB, // Keyboard_Key_PLUS
  0xBC, // Keyboard_Key_COMMA
  0xBD, // Keyboard_Key_MINUS
  0xBE, // Keyboard_Key_PERIOD
  0xBF, // Keyboard_Key_SLASH
  0xC0, // Keyboard_Key_GRAVE
  0xDB, // Keyboard_Key_LEFT_BRACKET
  0xDC, // Keyboard_Key_BACKSLASH
  0xDD, // Keyboard_Key_RIGHT_BRACKET
  0xDE, // Keyboard_Key_QUOTE
};

function u32 
_native_key_from_os_key(Keyboard_Key key)
{
  return _win32_key_table[key];
}

function Keyboard_Key 
_os_key_from_native_key(u32 native_key)
{
  for(u32 i = 0; i < Keyboard_Key_Count; ++i)
  {
    if(_win32_key_table[i] == native_key)
    {
      return (Keyboard_Key)i;
    }
  }
  return Keyboard_Key_Count; // invalid
}

///////////////////////////////////////////////////////
// @Section: OS Global State
///////////////////////////////////////////////////////
// @Section: Entry point (Windows specific functions behind entry_point)

LRESULT CALLBACK 
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) 
  {
    case WM_SETCURSOR:
    {
      if (LOWORD(lParam) == HTCLIENT) 
      {
        os_cursor_set(CURSOR_ARROW);
        return true;
      }
    }
    break;

    case WM_SIZE: 
    {
      _win32_window_resize_callback(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }
    break;

    // Keyboard keys
    case WM_KEYDOWN: 
    {
      Keyboard_Key key = _os_key_from_native_key((u32)wParam);
      if (key < Keyboard_Key_Count) 
      {
        _input_process_keyboard_key((Keyboard_Key)key, true);
      }
      else
      {
        // TODO(fz): Handle error
      }
      return 0;
    }
    break;
    case WM_KEYUP: 
    {
      Keyboard_Key key = _os_key_from_native_key((u32)wParam);
      if (key < Keyboard_Key_Count) 
      {
        _input_process_keyboard_key((Keyboard_Key)key, false);
      }
      else
      {
        // TODO(fz): Handle error
      }
      return 0;
    }
    break;

    // Mouse Cursor
    case WM_MOUSEMOVE: 
    {
      if (_IgnoreNextMouseMove) 
      {
        _IgnoreNextMouseMove = false;
        return 0;
      }
      s32 x = LOWORD(lParam);
      s32 y = HIWORD(lParam);
      _input_process_mouse_cursor((f32)x, (f32)y);
      return 0;
    }
    break;
    
    // Mouse Buttons
    case WM_LBUTTONDOWN: 
    {
      _input_process_mouse_button(MouseButton_Left, true);
      return 0;
    }
    break;
    case WM_LBUTTONUP: 
    {
      _input_process_mouse_button(MouseButton_Left, false);
      return 0;
    }
    break;
    case WM_RBUTTONDOWN: 
    {
      _input_process_mouse_button(MouseButton_Right, true);
      return 0;
    }
    break;
    case WM_RBUTTONUP: 
    {
      _input_process_mouse_button(MouseButton_Right, false);
      return 0;
    }
    break;
    case WM_MBUTTONDOWN: 
    {
      _input_process_mouse_button(MouseButton_Middle, true);
      return 0;
    }
    break;
    case WM_MBUTTONUP: 
    {
      _input_process_mouse_button(MouseButton_Middle, false);
      return 0;
    }
    break;

    case WM_CLOSE:
    {
      DestroyWindow(hWnd);
      return 0;
    }
    break;

    case WM_DESTROY: 
    {
    #if 0 // TODO(Fz): check for opengl
      wglMakeCurrent(null, null);
      wglDeleteContext(_RenderingContextHandle);
    #endif
      ReleaseDC(hWnd, _DeviceContextHandle);
      PostQuitMessage(0);
      return 0;
    }
    break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}


int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
  SetUnhandledExceptionFilter(&win32_exception_filter);
  _hInstance = hInstance;

  // Dynamically load windows functions which are not guaranteed in all SDKs
  {
    HMODULE module = LoadLibraryA("kernel32.dll");
    w32_SetThreadDescription_func = (W32_SetThreadDescription_Type *)GetProcAddress(module, "SetThreadDescription");
    FreeLibrary(module);
  }

  local_persist Thread_Context thread_context;
  thread_context_init_and_attach(&thread_context);

  // Prepare window (still requires calling os_window_open in user layer to actually open it).
  {
    _input_init();
    _WindowHandle = _win32_window_create(_hInstance, 600, 600);
    if (!_WindowHandle)
    {
      ERROR_MESSAGE_AND_EXIT("Failed to get window handle\n");
      return false;
    }
    _DeviceContextHandle = GetDC(_WindowHandle);
    if (!_DeviceContextHandle)
    {
        ERROR_MESSAGE_AND_EXIT("Failed to get device context\n");
        return false;
    }
  }
  
  main_thread_base_entry_point(__argc, __argv);
  return _ApplicationReturn;
}

///////////////////////////////////////////////////////
// @Section: Window

function HWND
_win32_window_create(HINSTANCE hInstance, s32 width, s32 height)
{
  HWND result = {0};
  WNDCLASSEXA wc = {
    .cbSize        = sizeof(wc),
    .lpfnWndProc   = WndProc,
    .hInstance     = hInstance,
    .hIcon         = LoadIconA(NULL, MAKEINTRESOURCEA(IDI_APPLICATION)),
    .hCursor       = LoadCursorA(NULL, MAKEINTRESOURCEA(IDC_ARROW)),
    .lpszClassName = "FZ_Window_Class",
  };

  ATOM atom = RegisterClassExA(&wc);
  Assert(atom && "Failed to register window class");
    
  DWORD exstyle = WS_EX_APPWINDOW;
  DWORD style   = WS_OVERLAPPEDWINDOW;
  result = CreateWindowExA(exstyle, wc.lpszClassName, "FZ_Window_Title", style, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, wc.hInstance, NULL);

  if (!result) 
  {
    win32_debug_output_last_error(S("CreateWindowExA"));
  }
  return result;
}

function void
_win32_window_resize_callback(s32 width, s32 height)
{
  if (height == 0) height = 1;
  if (width == 0)  width  = 1;
  _WindowDimensions.x = width;
  _WindowDimensions.y = height;

#if 0
  // TODO(fz): Figure out how to do this without opengl definitions
  if (_IsOpenGLContextEnabled)
  {
    glViewport(0, 0, width, height);
  }
#endif 
}

///////////////////////////////////////////////////////
// @Section: Error handling

function LONG WINAPI
win32_exception_filter(EXCEPTION_POINTERS* exception_ptrs)
{
  // TODO(fz): Implement
  ExitProcess(1);
}

function void
win32_debug_output_last_error(String8 context)
{
  DWORD err = GetLastError();
  if (err == 0) return;

  LPWSTR messageBuffer = NULL;
  FormatMessageW(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    err,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPWSTR)&messageBuffer,
    0,
    NULL);

  if (messageBuffer)
  {
    // Convert wide string to narrow string (UTF-8 or ANSI) for OutputDebugStringA
    int size_needed = WideCharToMultiByte(CP_ACP, 0, messageBuffer, -1, NULL, 0, NULL, NULL);
    if (size_needed > 0)
    {
      char* messageA = (char*)HeapAlloc(GetProcessHeap(), 0, size_needed);
      if (messageA)
      {
        Scratch scratch = scratch_begin(0,0);
        char* cstring_context = cstring_from_string8(scratch.arena, context);
        WideCharToMultiByte(CP_ACP, 0, messageBuffer, -1, messageA, size_needed, NULL, NULL);
        OutputDebugStringA(cstring_context);
        OutputDebugStringA(": ");
        OutputDebugStringA(messageA);
        OutputDebugStringA("\n");
        HeapFree(GetProcessHeap(), 0, messageA);
        scratch_end(&scratch);
      }
    }
    LocalFree(messageBuffer);
  }
}