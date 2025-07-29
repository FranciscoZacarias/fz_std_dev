
#define DEBUG 1
#include "fz_base.h"
#include "fz_window.h"
#include "fz_opengl.h"

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(400, 400, S("fz_std_tests"));
  os_window_open();
  os_opengl_init();

  while(g_is_program_running)
  {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    os_window_swap_buffers();
  }
}