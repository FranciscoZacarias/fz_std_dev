function void
main_thread_base_entry_point(int argc, char **argv)
{
  Scratch scratch = scratch_begin(0, 0);
  Command_Line cmd_line = command_line_parse_from_argc_argv(argc, argv);
  entry_point(&cmd_line);
  scratch_end(&scratch);
}