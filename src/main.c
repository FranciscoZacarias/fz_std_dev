#define DEBUG 1
#include "fz_base.h"
#include "fz_window.h"
#include "fz_opengl.h"

function void
input_update()
{
  if (input_is_key_pressed(Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }
}

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(400, 400, S("fz_std_tests"));
  os_opengl_init();
  os_window_open();

  f32 phase = 0.0f;
  const f32 speed = 0.05f;
  const f32 tau = PI*2;

  os_window_enable_vsync(true);
  while(os_is_application_running())
  {
    input_update();

    phase += speed;
    if (phase > tau) phase -= tau;
    f32 t = (1.0f + cosf(phase)) * 0.5f;
    f32 r = (1.0f + cosf(phase)) * 0.5f;
    f32 g = (1.0f + cosf(phase - tau/3)) * 0.5f;
    f32 b = (1.0f + cosf(phase - 2*tau/3)) * 0.5f;
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    os_swap_buffers();
  }
}
