
#define ENABLE_ASSERT 1
#include "fz_base.h"
#include "fz_window.h"
#include "fz_opengl.h"

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(400, 400, S("asd"));
  os_window_open();
  os_opengl_init();

  while(g_is_program_running)
  {

    os_window_swap_buffers();
  }
}