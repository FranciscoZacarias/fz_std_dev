function void
error_init(String8 error_log_path)
{
  AssertNoReentry();
  MemoryZeroStruct(&g_error_context);
  g_error_context.arena = arena_alloc();
  g_error_context.log_file_path     = string8_copy(g_error_context.arena, error_log_path);
  g_error_context.error_entry_first = NULL;
  g_error_context.error_entry_last  = NULL;
  g_error_context.error_count       = 0;
}

function void 
error_emit(Error_Level level, String8 message, String8 file, u32 line)
{
  if (!g_error_context.arena)
  {
    printf("Global error context not initialized.");
    return;
  }

  Error_Entry_Node* error_entry_node = 0;
  if (g_error_context.error_count < MAX_ERROR_NODES)
  {
    error_entry_node = push_array(g_error_context.arena, Error_Entry_Node, 1);
    error_entry_node->next = 0;
  
    if (g_error_context.error_entry_last)
    {
      g_error_context.error_entry_last->next = error_entry_node;
    }
    else
    {
      g_error_context.error_entry_first = error_entry_node;
    }
    g_error_context.error_entry_last = error_entry_node;
    g_error_context.error_count++;
  }
  else
  {
    error_entry_node = g_error_context.error_entry_first;
    g_error_context.error_entry_first = g_error_context.error_entry_first->next;
  
    error_entry_node->next = 0;
    g_error_context.error_entry_last->next = error_entry_node;
    g_error_context.error_entry_last = error_entry_node;
  }

  error_entry_node->value.level     = level;
  error_entry_node->value.message   = string8_copy(g_error_context.arena, message);
  error_entry_node->value.file      = string8_copy(g_error_context.arena, file);
  error_entry_node->value.line      = line;
  error_entry_node->value.timestamp = 0; // os_now_microseconds(); TODO(fz): fix later

  if (g_error_context.log_file_path.size > 0)
  {
    String8 level_str = {0};
    switch (level)
    {
      case Error_Level_Info:    level_str = S("INFO");    break;
      case Error_Level_Warning: level_str = S("WARNING"); break;
      case Error_Level_Error:   level_str = S("ERROR");   break;
      case Error_Level_Fatal:   level_str = S("FATAL");   break;
      default:                  level_str = S("UNKNOWN"); break;
    }

    String8 log_line = string8_from_format(g_error_context.arena, "[%s] %.*s:%u: %.*s\n", level_str.str, (s32)file.size, file.str, line, (s32)message.size, message.str);
    os_file_append(g_error_context.log_file_path, log_line.str, log_line.size);
    os_console_write(log_line);
  }

  if (level == Error_Level_Fatal)
  {
    Breakpoint();
    os_exit_process(1);
  }
}