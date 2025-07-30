///////////////////////////////////////////////////////
// @Section: OS Handles

///////////////////////////////////////////////////////
// @Section: OS-Dependent implementation

#if OS_WINDOWS
# include "os/win32/os_win32.c"
#elif OS_LINUX
# include "os/linux/os_linux.c"
#else
# error OS core layer not implemented for this operating system.
#endif

///////////////////////////////////////////////////////
// @Section: Timer

function f64
os_time_in_seconds(OS_Time time)
{
  return (f64)time.microseconds / 1000000.0;
}

function f64
os_time_in_milliseconds(OS_Time time)
{
  return (f64)time.microseconds / 1000.0;
}

function u64
os_time_in_microseconds(OS_Time time)
{
  return time.microseconds;
}

function OS_Time
os_time_diff(OS_Time start, OS_Time end)
{
  OS_Time result = {0};
  result.microseconds = end.microseconds - start.microseconds;
  return result;
}

function void
_update_frame_info()
{
  g_os_frame_info_previous = g_os_frame_info_current;

  OS_Time now        = os_time_now_microseconds();
  OS_Time frame_time = os_time_diff(g_os_frame_info_previous.frame_start, now);

  g_os_frame_info_current.frame_start = now;
  g_os_frame_info_current.frame_time  = frame_time;
  g_os_frame_info_current.frame_count = g_os_frame_info_previous.frame_count + 1;
}

///////////////////////////////////////////////////////
// @Section: Misc
function f32
os_get_fps()
{
  f32 result = 0.0f;

  // Assuming g_os_frame_info is updated per frame and frame_time is valid
  f64 frame_time_sec = os_time_in_seconds(g_os_frame_info_current.frame_time);

  if (frame_time_sec > 0.0)
  {
    result = (f32)(1.0 / frame_time_sec);
  }

  return result;
}
