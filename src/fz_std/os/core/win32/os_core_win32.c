
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
// @Section: Win32 functions

LRESULT CALLBACK 
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) 
  {
    case WM_SETCURSOR:
    {
      if (LOWORD(lParam) == HTCLIENT) 
      {
        win32_set_cursor(CURSOR_ARROW);
        return true;
      }
    } break;

    case WM_SIZE: 
    {
      _win32_window_resize_callback(LOWORD(lParam), HIWORD(lParam));
      return 0;
    } break;

    // Keyboard keys
    case WM_KEYDOWN: 
    {
      Keyboard_Key key = _os_key_from_native_key((u32)wParam);
      if (key < Keyboard_Key_Count) 
      {
        _input_process_keyboard_key((Keyboard_Key)wParam, true);
      }
      else
      {
        // TODO(fz): Handle error
      }
      return 0;
    } break;
    case WM_KEYUP: 
    {
      Keyboard_Key key = _os_key_from_native_key((u32)wParam);
      if (key < Keyboard_Key_Count) 
      {
        _input_process_keyboard_key((Keyboard_Key)wParam, false);
      }
      else
      {
        // TODO(fz): Handle error
      }
      return 0;
    } break;

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
    } break;
    
    // Mouse Buttons
    case WM_LBUTTONDOWN: 
    {
      _input_process_mouse_button(MouseButton_Left, true);
      return 0;
    } break;
    case WM_LBUTTONUP: 
    {
      _input_process_mouse_button(MouseButton_Left, false);
      return 0;
    } break;
    case WM_RBUTTONDOWN: 
    {
      _input_process_mouse_button(MouseButton_Right, true);
      return 0;
    } break;
    case WM_RBUTTONUP: 
    {
      _input_process_mouse_button(MouseButton_Right, false);
      return 0;
    } break;
    case WM_MBUTTONDOWN: 
    {
      _input_process_mouse_button(MouseButton_Middle, true);
      return 0;
    } break;
    case WM_MBUTTONUP: 
    {
      _input_process_mouse_button(MouseButton_Middle, false);
      return 0;
    } break;

    case WM_DESTROY: 
    {
    #if 0 // TODO(Fz): check for opengl
      wglMakeCurrent(null, null);
      wglDeleteContext(_RenderingContextHandle);
    #endif
      ReleaseDC(hWnd, _DeviceContextHandle);
      PostQuitMessage(0);
      return 0;
    } break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
  SetUnhandledExceptionFilter(&win32_exception_filter);

  // dynamically load windows functions which are not guaranteed in all SDKs
  {
    HMODULE module = LoadLibraryA("kernel32.dll");
    w32_SetThreadDescription_func = (W32_SetThreadDescription_Type *)GetProcAddress(module, "SetThreadDescription");
    FreeLibrary(module);
  }

  _hInstance = hInstance;
  thread_context_init_and_attach(&MainThreadContext);
  Command_Line cmd_line = command_line_parse(lpCmdLine);
  main_thread_base_entry_point(__argc, __wargv);
  return 0;
}

function void
_win32_window_resize_callback(s32 width, s32 height) {
  if (height == 0) height = 1;
  if (width == 0)  width = 1;
  _WindowDimensions.x = width;
  _WindowDimensions.y = height;
  if (_IsOpenGLContextEnabled) {
    glViewport(0, 0, width, height);
  }
}

function LONG WINAPI
win32_exception_filter(EXCEPTION_POINTERS* exception_ptrs)
{
  // TODO(fz): Implement
  ExitProcess(1);
}