#ifndef OS_CORE_H
#define OS_CORE_H

///////////////////////////////////////////////////////
// @Section: System info
typedef struct OS_System_Info
{
  u32 logical_processor_count;
  u64 page_size;
  u64 large_page_size;
  u64 allocation_granularity;
  String8 machine_name;
} OS_System_Info;

///////////////////////////////////////////////////////
// @Section: Process Info
typedef struct OS_Process_Info
{
  u32 pid;
  b32 large_pages_allowed;
  String8 binary_path;
  String8 initial_path;
  String8 user_program_data_path;
  String8_List module_load_paths;
  String8_List environment;
} OS_Process_Info;

///////////////////////////////////////////////////////
// @Section: Process Launch Parameters
typedef struct OS_Launch_Parameters
{
  String8_List cmd_line;
  String8 path;
  String8_List env;
  b32 inherit_env;
  b32 debug_subprocesses;
  b32 consoleless;
} OS_Launch_Parameters;

///////////////////////////////////////////////////////
// @Section: Memory
typedef struct OS_Memory_Stats
{
  u64 total_physical;
  u64 available_physical;
  u64 total_virtual;
  u64 used_virtual;
} OS_Memory_Stats;

function OS_Memory_Stats os_memory_stats();                       /* Returns the current memory usage statistics of the system and process */
function void*           os_memory_reserve(u64 size);             /* Reserves a block of virtual address space without committing physical memory */
function b32             os_memory_commit(void *ptr, u64 size);   /* Commits physical memory to a reserved region */
function void            os_memory_decommit(void *ptr, u64 size); /* Decommits physical memory from a region, keeping the address space reserved */
function void            os_memory_release(void *ptr, u64 size);  /* Releases previously reserved memory, making the address space reusable */
function u64             os_memory_get_page_size();               /* Returns the operating system's memory page size */

///////////////////////////////////////////////////////
// @Section: Time
typedef struct PerformanceTimer
{
  u64 start_ticks;
  u64 end_ticks;
  f32 elapsed_seconds;
} Performance_Timer;

function void os_timer_init();                               /* Initializes performance timing */
function void os_timer_start(Performance_Timer* timer);      /* Starts the given timer */
function void os_timer_end(Performance_Timer* timer);        /* Stops the timer and calculates elapsed time */
function f32  os_get_elapsed_time();                         /* Returns time elapsed since program started */
function f32  os_get_frame_time();                           /* Returns time elapsed since last frame */

///////////////////////////////////////////////////////
// @Section: Console
function b32     os_console_init();                           /* Initializes the console (allocates or attaches on Windows, no-op on Unix) */
function void    os_console_write(String8 string);            /* Writes a UTF-8 string to the console without a newline */
function void    os_console_write_line(String8 string);       /* Writes a UTF-8 string to the console followed by a newline */
function void    os_console_writef(char *fmt, ...);           /* Formatted print to console, behaves like printf */
function void    os_console_set_text_color(u8 r, u8 g, u8 b); /* Sets console text color using RGB (only supported on capable terminals) */
function void    os_console_reset_text_color();               /* Resets console text color to default */
function String8 os_console_read_line(Arena *arena);          /* Reads a line from stdin into a String8 (blocking, newline-trimmed) */
function b32     os_console_has_input();                      /* Returns true if there is input available in the console buffer (non-blocking) */

///////////////////////////////////////////////////////
// @Section: Files
typedef struct File_Data
{
  String8 path;
  String8 data;
} File_Data;

typedef struct File_Node
{
  struct File_Node* next;
  File_Data value;
} File_Node;

typedef struct File_List
{
  File_Node* first;
  File_Node* last;
  u64 node_count;
  u64 total_size;
} File_List;

function b32       os_file_create(String8 path);                                       /* Creates file. If file exists, returns true anyway. */
function b32       os_file_delete(String8 path);                                       /* Deletes a file */
function b32       os_file_exists(String8 path);                                       /* Returns true if file exists */
function u32       os_file_overwrite(String8 path, u8* data, u64 data_size);           /* Wipes file contents and writes data */
function u32       os_file_append(String8 path, u8* data, u64 data_size);              /* Appends data to the file */
function b32       os_file_wipe(String8 path);                                         /* Clears file */
function u32       os_file_size(String8 path);                                         /* Returns the size of the file */
function File_Data os_file_load(Arena* arena, String8 path);                           /* Loads file into memory */
function b32       os_file_has_extension(String8 filename, String8 ext);               /* Checks the file extension */
function u64       os_file_get_last_modified_time(String8 path);                       /* Returns last time file as modified */

///////////////////////////////////////////////////////
// @Section: Directories
function b32     os_directory_create(String8 path);                    /* Creates a directory in a given path */
function b32     os_directory_delete(String8 path);                    /* Deletes a directory */
function b32     os_directory_move(String8 path, String8 destination); /* Moves directory in path to destination */
function String8 os_directory_pop(String8 path);                       /* Returns the previous directory */
function String8 os_directory_push(String8 path, String8 directory);   /* Changes directory. 'directory' must be in path */

///////////////////////////////////////////////////////
// @Section: Window Lifecycle
function void os_window_open(s32 width, s32 height, String8 title); /* Creates and shows a window */
function void os_window_close();                                    /* Closes and destroys a window */
function b32  os_window_swap_buffers();                             /* Swaps buffers for the only existing window */

///////////////////////////////////////////////////////
// @Section: Window Flags
function b32  os_window_is_fullscreen();         /* True if fullscreen */
function void os_window_set_fullscreen(b32 set); /* Enables/disables fullscreen */
function b32  os_window_is_maximized();          /* True if maximized */
function void os_window_set_maximized(b32 set);  /* Maximizes/restores window */
function b32  os_window_is_minimized();          /* True if minimized */
function void os_window_set_minimized(b32 set);  /* Minimizes/restores window */

///////////////////////////////////////////////////////
// @Section: Window Appearance
function void os_window_set_visible(b32 visible);                          /* Show or hide the window */
function b32  os_window_set_title(String8 title);                          /* Sets window title */
function void os_window_clear_custom_border_data();                        /* Resets border override (Windows only) */
function void os_window_push_custom_title_bar(f32 thickness);              /* Define title bar area */
function void os_window_push_custom_edges(f32 thickness);                  /* Define draggable edges */
function void os_window_push_custom_title_bar_client_area(Range2F32 rect); /* Client title bar rect */
function void os_window_set_position(Vec2F32 pos);                         /* Set window top-left position */
function void os_window_set_size(s32 width, s32 height);                   /* Set client size (non-fullscreen) */

///////////////////////////////////////////////////////
// @Section: Cursor
typedef enum Cursor_Type
{
  CURSOR_ARROW,
  CURSOR_HAND,
  CURSOR_CROSSHAIR,
  CURSOR_IBEAM,
  CURSOR_WAIT,
  CURSOR_SIZE_ALL,

  CURSOR_COUNT
} Cursor_Type;

function void os_cursor_set(Cursor_Type cursor);    /* Sets system cursor type */
function void os_cursor_set_position(s32 x, s32 y); /* Moves cursor to screen coordinates */
function void os_cursor_lock(b32 lock);             /* Locks/unlocks cursor to center */
function void os_cursor_hide(b32 hide);             /* Hides/shows the cursor */

///////////////////////////////////////////////////////
// @Section: Input
typedef enum Keyboard_Key
{
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

function u32          _native_key_from_os_key(Keyboard_Key key); /* Converts os key to native key */
function Keyboard_Key _os_key_from_native_key(u32 native_key);   /* Converts native key to os key */

typedef enum Mouse_Button
{
  MouseButton_Left,
  MouseButton_Right,
  MouseButton_Middle,
  
  MouseButton_Count,
} Mouse_Button;

#define KEYBOARD_STATE_SIZE 256
typedef struct Keyboard_State
{
  b8 keys[KEYBOARD_STATE_SIZE];
} Keyboard_State;

typedef struct Mouse_State
{
  Vec2F32 screen_space;
  Vec2F32 delta;
  b8 buttons[MouseButton_Count];
} Mouse_State;

typedef struct Input_State
{
  Keyboard_State keyboard_current;
  Keyboard_State keyboard_previous;
  Mouse_State   mouse_current;
  Mouse_State   mouse_previous;
} Input_State;

global Input_State _InputState;

function void _input_init();   /* Initializes input state (clears previous + current states) */
function void _input_update(); /* Updates previous input state with current state (to track deltas and transitions) */

///////////////////////////////////////////////////////
// @Section: Keyboard keys
function b32 input_is_key_up(Keyboard_Key key);      /* True if the given key is currently up */
function b32 input_is_key_down(Keyboard_Key key);    /* True if the given key is currently down */
function b32 input_was_key_up(Keyboard_Key key);     /* True if the given key was up on the previous frame */
function b32 input_was_key_down(Keyboard_Key key);   /* True if the given key was down on the previous frame */
function b32 input_is_key_pressed(Keyboard_Key key); /* True if the given key is down this frame but was up last frame */

///////////////////////////////////////////////////////
// @Section: Mouse keys
function b32 input_is_button_up(Mouse_Button button);      /* True if the given mouse button is currently up */
function b32 input_is_button_down(Mouse_Button button);    /* True if the given mouse button is currently down */
function b32 input_was_button_up(Mouse_Button button);     /* True if the given mouse button was up on the previous frame */
function b32 input_was_button_down(Mouse_Button button);   /* True if the given mouse button was down on the previous frame */
function b32 input_is_button_pressed(Mouse_Button button); /* True if the given mouse button is down this frame but was up last frame */

///////////////////////////////////////////////////////
// @Section: Input Processing
function void _input_process_keyboard_key(Keyboard_Key key, b8 is_pressed);     /* Internal: Processes a key press/release and updates keyboard state */
function void _input_process_mouse_button(Mouse_Button button, b32 is_pressed); /* Internal: Processes mouse button press/release and updates mouse state */
function void _input_process_mouse_cursor(s32 x, s32 y);                        /* Internal: Updates current mouse cursor position in screen space */

///////////////////////////////////////////////////////
// @Section: OS Global State
typedef struct OS_State
{
  OS_System_Info system_info;
  OS_Process_Info process_info;
  u64 microsecond_resolution;
} OS_State;

global OS_State OSState = {0};

///////////////////////////////////////////////////////
// @Section: Entry point
function void entry_point(Command_Line* command_line); /* Application entry point implemented by the user */

///////////////////////////////////////////////////////
// @Section: Globals
global Vec2S32 _WindowDimensions = {0};

global b32 _IgnoreNextMouseMove  = false;
global b32 _IsCursorLocked       = false;

global Performance_Timer _Timer_FrameTime   = {0};
global Performance_Timer _Timer_ElapsedTime = {0};

#endif // OS_CORE_H