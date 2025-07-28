
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
  
  // Allocate from arena (subtract 1 to exclude NULL terminator from size)
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
// @Section: OS Global State
///////////////////////////////////////////////////////
// @Section: Entry point (Windows specific functions behind entry_point)
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

  main_thread_base_entry_point(__argc, __argv);
  return _ApplicationReturn;
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
_win32_output_last_error(DWORD err)
{
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
        WideCharToMultiByte(CP_ACP, 0, messageBuffer, -1, messageA, size_needed, NULL, NULL);
        OutputDebugStringA(": ");
        OutputDebugStringA(messageA);
        OutputDebugStringA("\n");
        HeapFree(GetProcessHeap(), 0, messageA);
      }
    }
    LocalFree(messageBuffer);
  }
}