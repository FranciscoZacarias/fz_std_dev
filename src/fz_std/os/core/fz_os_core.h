#ifndef FZ_OS_CORE_H
#define FZ_OS_CORE_H

// @Section: Entry point
internal void entry_point(Command_Line command_line); /* Application entry point implemented by the user */

// @Section: OS Handle
typedef struct OS_Handle {
  U64 u64[1];
} OS_Handle;

// @Section: System info
typedef struct OS_System_Info {
  U32 logical_processor_count;
  U64 page_size;
  U64 large_page_size;
  U64 allocation_granularity;
  String8 machine_name;
} OS_System_Info;

// @Section: Process Info
typedef struct OS_Process_Info {
  U32 pid;
  B32 large_pages_allowed;
  String8 binary_path;
  String8 initial_path;
  String8 user_program_data_path;
  String8_List module_load_paths;
  String8_List environment;
} OS_Process_Info;

// @Section: Process Launch Parameters
typedef struct OS_Launch_Parameters {
  String8_List cmd_line;
  String8 path;
  String8_List env;
  B32 inherit_env;
  B32 debug_subprocesses;
  B32 consoleless;
  OS_Handle stdout_file;
  OS_Handle stderr_file;
  OS_Handle stdin_file;
} OS_Launch_Parameters;

// @Section: Memory
typedef struct OS_Memory_Stats {
  U64 total_physical;
  U64 available_physical;
  U64 total_virtual;
  U64 used_virtual;
} OS_Memory_Stats;

internal OS_Memory_Stats os_memory_stats();                       /* Returns the current memory usage statistics of the system and process */
internal void*           os_memory_reserve(U64 size);             /* Reserves a block of virtual address space without committing physical memory */
internal B32             os_memory_commit(void *ptr, U64 size);   /* Commits physical memory to a reserved region */
internal void            os_memory_decommit(void *ptr, U64 size); /* Decommits physical memory from a region, keeping the address space reserved */
internal void            os_memory_release(void *ptr, U64 size);  /* Releases previously reserved memory, making the address space reusable */
internal U64             os_memory_get_page_size();               /* Returns the operating system's memory page size */

// @Section: UUID
typedef struct OS_Uuid {
  U8 bytes[16];
} OS_Uuid;

internal OS_Uuid os_generate_uuid(void); /* Generates a 128-bit unique identifier (UUID v4). */

// @Section: Time
typedef struct PerformanceTimer {
#if OS_WINDOWS
  LARGE_INTEGER start;
  LARGE_INTEGER end;
#else
  # error OS Performance Timer not implemented for this operating system.
#endif
  F32 elapsed_seconds;
} PerformanceTimer;

internal void os_timer_init();                         /* Initializes performance timing */
internal void os_timer_start(PerformanceTimer* timer); /* Starts the given timer */
internal void os_timer_end(PerformanceTimer* timer);   /* Stops the timer and calculates elapsed time */
internal F32  os_get_elapsed_time();                   /* Returns time elapsed since last frame */

// @Section: Console
internal void    os_console_init()                           /* Initializes the console (allocates or attaches on Windows, no-op on Unix) */
internal void    os_console_write(String8 string)            /* Writes a UTF-8 string to the console without a newline */
internal void    os_console_write_line(String8 string)       /* Writes a UTF-8 string to the console followed by a newline */
internal void    os_console_writef(char *fmt, ...)           /* Formatted print to console, behaves like printf */
internal void    os_console_set_text_color(U8 r, U8 g, U8 b) /* Sets console text color using RGB (only supported on capable terminals) */
internal void    os_console_reset_text_color()               /* Resets console text color to default */
internal String8 os_console_read_line(Arena *arena)          /* Reads a line from stdin into a String8 (blocking, newline-trimmed) */
internal B32     os_console_has_input()                      /* Returns true if there is input available in the console buffer (non-blocking) */

// @Section: Files
typedef struct File_Data {
  String8 path;
  String8 data;
} File_Data;

typedef struct File_Node {
  struct File_Node* next;
  File_Data value;
} File_Node;

typedef struct File_List {
  File_Node* first;
  File_Node* last;
  U64 node_count;
  U64 total_size;
} File_List;

internal B32          os_file_create(String8 path);                                       /* Creates file. If file exists, returns true anyway. */
internal B32          os_file_exists(String8 path);                                       /* Returns true if file exists */
internal U32          os_file_overwrite(String8 path, U8* data, U64 data_size);           /* Wipes file contents and writes data */
internal U32          os_file_append(String8 path, U8* data, U64 data_size);              /* Appends data to the file */
internal B32          os_file_wipe(String8 path);                                         /* Clears file */
internal U32          os_file_size(String8 path);                                         /* Returns the size of the file */
internal File_Data    os_file_load(Arena* arena, String8 path);                           /* Loads file into memory */
internal B32          os_file_has_extension(String8 filename, String8 ext);               /* Checks the file extension */
internal U64          os_file_get_last_modified_time(String8 path);                       /* Returns last time file as modified */
internal String8_List os_file_get_all_file_paths_recursively(Arena* arena, String8 path); /* Returns all files paths recursively from the given path */

// @Section: Directories
internal B32     os_directory_create(String8 path);                    /* Creates a directory in a given path */
internal String8 os_directory_delete(String8 path);                    /* Deletes a directory */
internal String8 os_directory_move(String8 path, String8 destination); /* Moves directory in path to destination */
internal String8 os_directory_pop(String8 path);                       /* Returns the previous directory */
internal String8 os_directory_push(String8 path, String8 directory);   /* Changes directory. 'directory' must be in path */

// @Section: Paths
internal String8 os_path_new(Arena* arena, String8 path);          /* Ensures path is correct */
internal B32     os_path_is_file(String8 path);                    /* Checks if path points to a file */
internal B32     os_path_is_directory(String8 path);               /* Checks if path points to a directory */
internal String8 os_path_get_working_directory();                  /* Returns current working directory */
internal String8 os_path_get_file_name(String8 path);              /* Returns the file name of a path */
internal String8 os_path_get_file_name_no_ext(String8 path);       /* Returns the file name of a path without it's extension*/
internal String8 os_path_join(Arena* arena, String8 a, String8 b); /* Merges two paths together */
internal String8 os_path_get_current_directory_name(String8 path); /* Returns current directory name. If path points to a file, prints the directory it is in */

// @Section: Clipboard
internal void    os_clipboard_set(String8 text); /* Gets clipboard contents */
internal String8 os_clipboard_get(Arena* arena); /* Sets clipboard contents */

// @Section: Random
internal B32 os_get_entropy(void* out, U64 size); /* Fills 'out' with 'size' bytes of cryptographically secure random data. Returns true on success */

#endif // FZ_OS_CORE_H