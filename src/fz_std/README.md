
# (FZ) Personal standard library

Basic structure:

```c
#define ENABLE_ASSERT 1
#include "fz_base.h" // Required
#include "fz_window.h" // Launches window (requires base)
#include "fz_opengl.h" // Attaches opengl context to window (requires window)

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init(); // Available with fz_base.h
  os_window_init(400, 400, S("asd")); // Available with fz_window.h
  os_window_open(); // Available with fz_window.h
  os_opengl_init(); // Available with fz_opengl.h

  while(g_is_program_running) // g_is_program_running is Available with fz_base.h
  {

    os_window_swap_buffers(); // Available with window.h
  }
}

```