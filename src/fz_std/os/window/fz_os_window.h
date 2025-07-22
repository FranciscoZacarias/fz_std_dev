#ifndef FZ_OS_WINDOW_H
#define FZ_OS_WINDOW_H

// @Section: Window Lifecycle
internal OS_Handle os_window_open(Range2F32 rect, String8 title); /* Creates and shows a window */
internal void      os_window_close(OS_Handle window);             /* Closes and destroys a window */

// @Section: Window State
internal b32  os_window_is_focused(OS_Handle window);     /* Returns true if window is focused */
internal void os_window_focus(OS_Handle window);          /* Tries to focus the window */
internal void os_window_first_paint(OS_Handle window);    /* Forces first WM_PAINT */
internal void os_window_bring_to_front(OS_Handle window); /* Moves window to front */

// @Section: Window Flags
internal b32  os_window_is_fullscreen(OS_Handle window);         /* True if fullscreen */
internal void os_window_set_fullscreen(OS_Handle window, b32);   /* Enables/disables fullscreen */
internal b32  os_window_is_maximized(OS_Handle window);          /* True if maximized */
internal void os_window_set_maximized(OS_Handle window, b32);    /* Maximizes/restores window */
internal b32  os_window_is_minimized(OS_Handle window);          /* True if minimized */
internal void os_window_set_minimized(OS_Handle window, b32);    /* Minimizes/restores window */

// @Section: Window Appearance
internal void os_window_set_visible(OS_Handle window, b32 visible);                          /* Show or hide the window */
internal b32  os_window_set_title(OS_Handle window, String8 title);                          /* Sets window title */
internal void os_window_clear_custom_border_data(OS_Handle window);                          /* Resets border override (Windows only) */
internal void os_window_push_custom_title_bar(OS_Handle window, f32 thickness);              /* Define title bar area */
internal void os_window_push_custom_edges(OS_Handle window, f32 thickness);                  /* Define draggable edges */
internal void os_window_push_custom_title_bar_client_area(OS_Handle window, Range2F32 rect); /* Client title bar rect */
internal void os_window_set_position(OS_Handle window, Vec2F32 pos);                         /* Set window top-left position */
internal void os_window_set_size(OS_Handle window, Vec2F32 size);                            /* Set client size (non-fullscreen) */

// @Section: Window Geometry
internal Range2F32 os_rect_from_window(OS_Handle window);                      /* Returns outer window rectangle */
internal Range2F32 os_client_rect_from_window(OS_Handle window);               /* Returns client area rectangle */
internal void      os_window_set_monitor(OS_Handle window, OS_Handle monitor); /* Moves window to monitor */
internal f32       os_dpi_from_window(OS_Handle window);                       /* DPI scale factor for the current window */

// @Section: Monitor
typedef struct OS_Monitor_Info {
  Range2F32 rect;      /* Physical monitor bounds in pixels */
  Range2F32 work_rect; /* Usable area (excludes taskbar/docks) */
  f32       dpi_scale; /* Scaling factor for monitor */
} OS_Monitor_Info;

internal u32             os_get_monitor_count();                   /* Number of active monitors */
internal OS_Handle       os_get_monitor_handle(u32 index);         /* Get monitor handle */
internal OS_Handle       os_get_primary_monitor();                 /* Get primary monitor */
internal OS_Handle       os_monitor_from_window(OS_Handle window); /* Monitor containing window */
internal OS_Monitor_Info os_get_monitor_info(OS_Handle monitor);   /* Info for monitor */
internal f32             os_dpi_from_monitor(OS_Handle monitor);   /* DPI scale factor for a given monitor */

// @Section: Cursor
typedef enum Cursor_Type {
  CURSOR_ARROW,
  CURSOR_HAND,
  CURSOR_CROSSHAIR,
  CURSOR_IBEAM,
  CURSOR_WAIT,
  CURSOR_SIZE_ALL,

  CURSOR_COUNT
} Cursor_Type;

internal void os_cursor_set(Cursor_Type cursor);    /* Sets system cursor type */
internal void os_cursor_set_position(s32 x, s32 y); /* Moves cursor to screen coordinates */
internal void os_cursor_lock(b32 lock);             /* Locks/unlocks cursor to center */
internal void os_cursor_hide(b32 hide);             /* Hides/shows the cursor */

// @Section: Input
typedef enum Keyboard_Key {
  Keyboard_Key_BACKSPACE,
  Keyboard_Key_ENTER,
  Keyboard_Key_TAB,
  Keyboard_Key_SHIFT,
  Keyboard_Key_CONTROL,
  Keyboard_Key_PAUSE,
  Keyboard_Key_CAPS_LOCK,
  Keyboard_Key_ESCAPE,
  Keyboard_Key_CONVERT,
  Keyboard_Key_NONCONVERT,
  Keyboard_Key_ACCEPT,
  Keyboard_Key_MODECHANGE,
  Keyboard_Key_SPACE,
  Keyboard_Key_PRIOR,
  Keyboard_Key_NEXT,
  Keyboard_Key_END,
  Keyboard_Key_HOME,
  Keyboard_Key_ARROW_LEFT,
  Keyboard_Key_ARROW_UP,
  Keyboard_Key_ARROW_RIGHT,
  Keyboard_Key_ARROW_DOWN,
  Keyboard_Key_SELECT,
  Keyboard_Key_PRINT,
  Keyboard_Key_EXECUTE,
  Keyboard_Key_SNAPSHOT,
  Keyboard_Key_INSERT,
  Keyboard_Key_DELETE,
  Keyboard_Key_HELP,
  Keyboard_Key_0,
  Keyboard_Key_1,
  Keyboard_Key_2,
  Keyboard_Key_3,
  Keyboard_Key_4,
  Keyboard_Key_5,
  Keyboard_Key_6,
  Keyboard_Key_7,
  Keyboard_Key_8,
  Keyboard_Key_9,
  Keyboard_Key_A,
  Keyboard_Key_B,
  Keyboard_Key_C,
  Keyboard_Key_D,
  Keyboard_Key_E,
  Keyboard_Key_F,
  Keyboard_Key_G,
  Keyboard_Key_H,
  Keyboard_Key_I,
  Keyboard_Key_J,
  Keyboard_Key_K,
  Keyboard_Key_L,
  Keyboard_Key_M,
  Keyboard_Key_N,
  Keyboard_Key_O,
  Keyboard_Key_P,
  Keyboard_Key_Q,
  Keyboard_Key_R,
  Keyboard_Key_S,
  Keyboard_Key_T,
  Keyboard_Key_U,
  Keyboard_Key_V,
  Keyboard_Key_W,
  Keyboard_Key_X,
  Keyboard_Key_Y,
  Keyboard_Key_Z,
  Keyboard_Key_LEFT_WIN,
  Keyboard_Key_RIGHT_WIN,
  Keyboard_Key_APPS,
  Keyboard_Key_SLEEP,
  Keyboard_Key_NUMPAD0,
  Keyboard_Key_NUMPAD1,
  Keyboard_Key_NUMPAD2,
  Keyboard_Key_NUMPAD3,
  Keyboard_Key_NUMPAD4,
  Keyboard_Key_NUMPAD5,
  Keyboard_Key_NUMPAD6,
  Keyboard_Key_NUMPAD7,
  Keyboard_Key_NUMPAD8,
  Keyboard_Key_NUMPAD9,
  Keyboard_Key_NUMPAD_MULTIPLY,
  Keyboard_Key_NUMPAD_ADD,
  Keyboard_Key_NUMPAD_SEPARATOR,
  Keyboard_Key_NUMPAD_SUBTRACT,
  Keyboard_Key_NUMPAD_DECIMAL,
  Keyboard_Key_NUMPAD_DIVIDE,
  Keyboard_Key_F1,
  Keyboard_Key_F2,
  Keyboard_Key_F3,
  Keyboard_Key_F4,
  Keyboard_Key_F5,
  Keyboard_Key_F6,
  Keyboard_Key_F7,
  Keyboard_Key_F8,
  Keyboard_Key_F9,
  Keyboard_Key_F10,
  Keyboard_Key_F11,
  Keyboard_Key_F12,
  Keyboard_Key_F13,
  Keyboard_Key_F14,
  Keyboard_Key_F15,
  Keyboard_Key_F16,
  Keyboard_Key_F17,
  Keyboard_Key_F18,
  Keyboard_Key_F19,
  Keyboard_Key_F20,
  Keyboard_Key_F21,
  Keyboard_Key_F22,
  Keyboard_Key_F23,
  Keyboard_Key_F24,
  Keyboard_Key_NUMLOCK,
  Keyboard_Key_SCROLL,
  Keyboard_Key_NUMPAD_EQUAL,
  Keyboard_Key_LEFT_SHIFT,
  Keyboard_Key_RIGHT_SHIFT,
  Keyboard_Key_LEFT_CONTROL,
  Keyboard_Key_RIGHT_CONTROL,
  Keyboard_Key_LEFT_MENU,
  Keyboard_Key_RIGHT_MENU,
  Keyboard_Key_SEMICOLON,
  Keyboard_Key_PLUS,
  Keyboard_Key_COMMA,
  Keyboard_Key_MINUS,
  Keyboard_Key_PERIOD,
  Keyboard_Key_SLASH,
  Keyboard_Key_GRAVE,
  Keyboard_Key_LEFT_BRACKET,
  Keyboard_Key_BACKSLASH,
  Keyboard_Key_RIGHT_BRACKET,
  Keyboard_Key_QUOTE,
  
  Keyboard_Key_Count,
} Keyboard_Key;

internal u32          _native_key_from_os_key(Keyboard_Key key); /* Converts os key to native key */
internal Keyboard_Key _os_key_from_native_key(u32 native_key);   /* Converts native key to os key */

typedef enum Mouse_Button {
  MouseButton_Left,
  MouseButton_Right,
  MouseButton_Middle,
  
  MouseButton_Count,
} Mouse_Button;

#define KEYBOARD_STATE_SIZE 256
typedef struct Keyboard_State {
  b8 keys[KEYBOARD_STATE_SIZE];
} Keyboard_State;

typedef struct Mouse_State {
  union {
    struct {
      f32 screen_space_x;
      f32 screen_space_y;
    };
    Vec2F32 screen_space;
  };
  union {
    struct {
      f32 delta_x;
      f32 delta_y;
    };
    Vec2F32 delta;
  };
  b8 buttons[MouseButton_Count];
} Mouse_State;

typedef struct Input_State {
  Keyboard_State keyboard_current;
  Keyboard_State keyboard_previous;
  Mouse_State   mouse_current;
  Mouse_State   mouse_previous;
} Input_State;

global Input_State _InputState;

internal void _input_init();   /* Initializes input state (clears previous + current states) */
internal void _input_update(); /* Updates previous input state with current state (to track deltas and transitions) */

// Keyboard keys
internal b32 input_is_key_up(Keyboard_Key key);      /* True if the given key is currently up */
internal b32 input_is_key_down(Keyboard_Key key);    /* True if the given key is currently down */
internal b32 input_was_key_up(Keyboard_Key key);     /* True if the given key was up on the previous frame */
internal b32 input_was_key_down(Keyboard_Key key);   /* True if the given key was down on the previous frame */
internal b32 input_is_key_pressed(Keyboard_Key key); /* True if the given key is down this frame but was up last frame */

// Mouse keys
internal b32 input_is_button_up(Mouse_Button button);      /* True if the given mouse button is currently up */
internal b32 input_is_button_down(Mouse_Button button);    /* True if the given mouse button is currently down */
internal b32 input_was_button_up(Mouse_Button button);     /* True if the given mouse button was up on the previous frame */
internal b32 input_was_button_down(Mouse_Button button);   /* True if the given mouse button was down on the previous frame */
internal b32 input_is_button_pressed(Mouse_Button button); /* True if the given mouse button is down this frame but was up last frame */

// Processing
internal void _input_process_keyboard_key(Keyboard_Key key, b8 is_pressed);     /* Internal: Processes a key press/release and updates keyboard state */
internal void _input_process_mouse_button(Mouse_Button button, b32 is_pressed); /* Internal: Processes mouse button press/release and updates mouse state */
internal void _input_process_mouse_cursor(s32 x, s32 y);                        /* Internal: Updates current mouse cursor position in screen space */

#endif // FZ_OS_WINDOW_H