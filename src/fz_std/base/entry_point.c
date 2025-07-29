function void
main_thread_base_entry_point(int argc, char **argv)
{
  Scratch scratch = scratch_begin(0, 0);

  // Setup error system
  {
    String8 error_log_path = os_executable_path(scratch.arena);
    error_log_path = os_directory_pop(error_log_path);
    error_init(error_log_path);
  }

  os_timer_init();
  Command_Line cmd_line = command_line_parse_from_argc_argv(argc, argv);
  entry_point(&cmd_line);
  scratch_end(&scratch);
}