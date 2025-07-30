function void
log_init(String8 log_path)
{
  AssertNoReentry();
  MemoryZeroStruct(&g_log_context);
  g_log_context.arena = arena_alloc();
  g_log_context.log_file_path   = string8_copy(g_log_context.arena, string8_concat(g_log_context.arena, log_path, S("\\fz.log")));
  g_log_context.log_entry_first = NULL;
  g_log_context.log_entry_last  = NULL;
  g_log_context.log_count       = 0;
}

function void 
log_emit(Log_Level level, String8 message, String8 file, u32 line)
{
  if (!g_log_context.arena)
  {
    printf("Global error context not initialized.");
    return;
  }
  Scratch scratch = scratch_begin(0,0);

  Log_Entry_Node* log_entry_node = 0;
  if (g_log_context.log_count < MAX_ERROR_NODES)
  {
    log_entry_node = push_array(g_log_context.arena, Log_Entry_Node, 1);
    log_entry_node->next = 0;
  
    if (g_log_context.log_entry_last)
    {
      g_log_context.log_entry_last->next = log_entry_node;
    }
    else
    {
      g_log_context.log_entry_first = log_entry_node;
    }
    g_log_context.log_entry_last = log_entry_node;
    g_log_context.log_count++;
  }
  else
  {
    log_entry_node = g_log_context.log_entry_first;
    g_log_context.log_entry_first = g_log_context.log_entry_first->next;
  
    log_entry_node->next = 0;
    g_log_context.log_entry_last->next = log_entry_node;
    g_log_context.log_entry_last = log_entry_node;
  }

  log_entry_node->value.level     = level;
  log_entry_node->value.message   = string8_copy(g_log_context.arena, message);
  log_entry_node->value.file      = string8_copy(g_log_context.arena, file);
  log_entry_node->value.line      = line;
  log_entry_node->value.timestamp = os_datetime_now();

  if (g_log_context.log_file_path.size > 0)
  {
    String8 level_str = {0};
    switch (level)
    {
      case Log_Level_Info:    level_str = S("INFO");    break;
      case Log_Level_Warning: level_str = S("WARNING"); break;
      case Log_Level_Error:   level_str = S("ERROR");   break;
      case Log_Level_Fatal:   level_str = S("FATAL");   break;
      default:                level_str = S("UNKNOWN"); break;
    }
    
    OS_Date_Time date = log_entry_node->value.timestamp;
    String8 log_line = string8_from_format(g_log_context.arena, 
      "%s :: %02d-%02d-%02d %02d:%02d:%02d :: %.*s:%u:\n%.*s\n", 
      level_str.str, date.year, date.month, date.day, date.hour, date.minute, date.second, (s32)file.size, file.str, line, (s32)message.size, message.str);
    os_file_append(g_log_context.log_file_path, log_line.str, log_line.size);
    os_console_write(log_line);
  }
  scratch_end(&scratch);
  if (level == Log_Level_Fatal)
  {
    Breakpoint();
    os_exit_process(1);
  }
}