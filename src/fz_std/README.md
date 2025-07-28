
# (FZ) Personal standard library

Basic structure:

```c
#include "fz_base.h" // Required
#include "fz_window.h" // Launches window (requires base)
#include "fz_opengl.h" // Attaches opengl context to window (requires window)

function void
entry_point()
{
  os_window_init(400, 400, S("asd"));
  os_window_open();
  os_console_init();

  for (;;)
  {

    os_window_swap_buffers();
  }
}
```