
#define ENABLE_ASSERT 1
#include "fz_base.h"
#include "fz_window.h"

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_window_init(400, 400, S("asd"));
  os_window_open();
  os_console_init();

  while(1)
  {

    os_window_swap_buffers();
  }
}