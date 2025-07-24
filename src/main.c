
#define ENABLE_ASSERT 1
#include "fz_base.h"

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_open(400, 400, S("asd"));

  while(os_window_swap_buffers())
  {
  }
}