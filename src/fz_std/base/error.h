#ifndef ERROR_H
#define ERROR_H

typedef enum
{
  Error_Level_Info = 0,
  Error_Level_Warning,
  Error_Level_Error,
  Error_Level_Fatal,

  Error_Level_Count
} Error_Level;

typedef struct Error_Entry Error_Entry;
struct Error_Entry
{
  Error_Level level;
  String8 message;

  String8 file;
  u32     line;
  u64     timestamp;
};

#define MAX_ERROR_NODES 128
typedef struct Error_Entry_Node Error_Entry_Node;
struct Error_Entry_Node
{
  Error_Entry_Node* next;
  Error_Entry value;
};

typedef struct Error_Context Error_Context;
struct Error_Context
{
  Arena* arena;
  Error_Entry_Node* error_entry_first;
  Error_Entry_Node* error_entry_last;
  u32 error_count;
  String8 log_file_path;
};

global Error_Context g_error_context = {0};

function void error_init(String8 error_log_path);
function void error_emit(Error_Level level, String8 message, String8 file, u32 line);

#define emit_info(str8_msg)  error_emit(Error_Level_Info,   str8_msg, S(__FILE__), __LINE__)
#define emit_warn(str8_msg)  error_emit(Error_Level_Warning,str8_msg, S(__FILE__), __LINE__)
#define emit_error(str8_msg) error_emit(Error_Level_Error,  str8_msg, S(__FILE__), __LINE__)
#define emit_fatal(str8_msg) error_emit(Error_Level_Fatal,  str8_msg, S(__FILE__), __LINE__)

#endif // ERROR_H