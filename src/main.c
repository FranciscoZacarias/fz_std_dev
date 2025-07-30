
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
  os_opengl_init();
  os_window_open();

  while(os_is_application_running())
  {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    printf("FPS: %.4f\n", os_get_fps());
    printf("Frame:\n - frame_start: %llu\n - frame_time: %llu\n - frame_count: %llu\n", g_os_frame_info_current.frame_start.microseconds, g_os_frame_info_current.frame_time.microseconds, g_os_frame_info_current.frame_count);
    os_swap_buffers();
  }
}