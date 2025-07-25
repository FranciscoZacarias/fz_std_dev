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
// @Section: Window - OS Dependent

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