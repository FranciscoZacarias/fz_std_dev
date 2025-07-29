function b32
os_opengl_init()
{
  b32 result = true;

  _win32_load_webgl_functions();

  // set pixel format for OpenGL context
  {
    int attrib[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB,     24,
      WGL_DEPTH_BITS_ARB,     24,
      WGL_STENCIL_BITS_ARB,   8,

      // uncomment for sRGB framebuffer, from WGL_ARB_framebuffer_sRGB extension
      // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_framebuffer_sRGB.txt
      //WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,

      // uncomment for multisampled framebuffer, from WGL_ARB_multisample extension
      // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multisample.txt
      //WGL_SAMPLE_BUFFERS_ARB, 1,
      //WGL_SAMPLES_ARB,        4, // 4x MSAA

      0,
    };

    int format;
    UINT formats;
    if (!wglChoosePixelFormatARB(g_os_window_win32.device_context, attrib, NULL, 1, &format, &formats) || formats == 0)
    {
      printf("OpenGL does not support required pixel format!");
      return false;
    }

    PIXELFORMATDESCRIPTOR desc = { .nSize = sizeof(desc) };
    int ok = DescribePixelFormat(g_os_window_win32.device_context, format, sizeof(desc), &desc);
    Assert(ok && "Failed to describe OpenGL pixel format");

    if (!SetPixelFormat(g_os_window_win32.device_context, format, &desc))
    {
      printf("Cannot set OpenGL selected pixel format!");
      return false;
    }
  }

  // create modern OpenGL context
  {
    int attrib[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
      WGL_CONTEXT_MINOR_VERSION_ARB, 6,
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,

      // ask for debug context for non "Release" builds
      // this is so we can enable debug callback
      WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,

      0,
    };

    g_os_window_win32.rendering_context = wglCreateContextAttribsARB(g_os_window_win32.device_context, NULL, attrib);
    if (!g_os_window_win32.rendering_context)
    {
      printf("Cannot create modern OpenGL context! OpenGL version 4.6 not supported?");
      return false;
    }

    result = wglMakeCurrent(g_os_window_win32.device_context, g_os_window_win32.rendering_context);
    win32_check_error();
    Assert(result && "Failed to make current OpenGL context");

    if (!_os_opengl_load_functions())
    {
      printf("Opengl failed to load functions");
      return false;
    }

    // enable debug callback
    glDebugMessageCallback(&_os_opengl_debug_callback, NULL);

    Assert(glEnable && "glEnable not loaded");
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  }

  return result;
}

function void
os_opengl_end()
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(g_os_window_win32.rendering_context);
}

function b32
_win32_load_webgl_functions()
{
  // to get WGL functions we need valid GL context, so create dummy window for dummy GL context
  HWND dummy = CreateWindowExW(
    0, L"STATIC", L"DummyWindow", WS_OVERLAPPED,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, NULL, NULL);
  if (!dummy)
  {
    printf("Failed to create dummy window");
    return false;
  }

  HDC device_context = GetDC(dummy);
  if (!device_context)
  {
    printf("Failed to get device context for dummy window");
    return false;
  }

  PIXELFORMATDESCRIPTOR desc = {
    .nSize      = sizeof(desc),
    .nVersion   = 1,
    .dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    .iPixelType = PFD_TYPE_RGBA,
    .cColorBits = 24,
  };

  int format = ChoosePixelFormat(device_context, &desc);
  if (!format) 
  {
    printf("Cannot choose OpenGL pixel format for dummy window!");
    return false;
  }

  if (!DescribePixelFormat(device_context, format, sizeof(desc), &desc))
  {
    printf("Failed to describe OpenGL pixel format");
    return false;
  }

  // reason to create dummy window is that SetPixelFormat can be called only once for the window
  if (!SetPixelFormat(device_context, format, &desc))
  {
    printf("Cannot set OpenGL pixel format for dummy window!");
    return false;
  }

  HGLRC rc = wglCreateContext(device_context);
  if (!rc)
  {
    printf("Failed to create OpenGL context for dummy window");
    return false;
  }

  if (!wglMakeCurrent(device_context, rc))
  {
    printf("Failed to make current OpenGL context for dummy window");
    return false;
  }

  {
    #define WGL_FUNC(ret, name, params) \
      name = (PFN##name##PROC)wglGetProcAddress(#name); \
      if (!name) { printf("%s not loaded", #name); return false; }
    # include "win32_wgl_functions.inl"
    #undef WGL_FUNC
  }

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(rc);
  ReleaseDC(dummy, device_context);
  DestroyWindow(dummy);

  return true;
}