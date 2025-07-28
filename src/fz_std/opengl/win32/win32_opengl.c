function b32
os_opengl_init()
{
  b32 result = true;

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
    if (!wglChoosePixelFormatARB(_DeviceContextHandle, attrib, NULL, 1, &format, &formats) || formats == 0)
    {
        printf("OpenGL does not support required pixel format!");
    }

    PIXELFORMATDESCRIPTOR desc = { .nSize = sizeof(desc) };
    int ok = DescribePixelFormat(_DeviceContextHandle, format, sizeof(desc), &desc);
    Assert(ok && "Failed to describe OpenGL pixel format");

    if (!SetPixelFormat(_DeviceContextHandle, format, &desc))
    {
      printf("Cannot set OpenGL selected pixel format!");
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

    HGLRC rc = wglCreateContextAttribsARB(_DeviceContextHandle, NULL, attrib);
    if (!rc) {
      printf("Cannot create modern OpenGL context! OpenGL version 4.5 not supported?");
    }

    result = wglMakeCurrent(_DeviceContextHandle, rc);
    Assert(result && "Failed to make current OpenGL context");

    if (!gladLoadGL()) {
      printf("Failed to load OpenGL functions with glad!");
    }

    // enable debug callback
    glDebugMessageCallback(&opengl_debug_callback, NULL);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  }

  return result;
}

function void
_os_opengl_load_functions()
{

}

function void
_os_opengl_get_webgl_functions()
{
  // to get WGL functions we need valid GL context, so create dummy window for dummy GL context
  HWND dummy = CreateWindowExW(
    0, L"STATIC", L"DummyWindow", WS_OVERLAPPED,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, NULL, NULL);
  Assert(dummy && "Failed to create dummy window");

  HDC dc = GetDC(dummy);
  Assert(dc && "Failed to get device context for dummy window");

  PIXELFORMATDESCRIPTOR desc = {
    .nSize = sizeof(desc),
    .nVersion = 1,
    .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    .iPixelType = PFD_TYPE_RGBA,
    .cColorBits = 24,
  };

  int format = ChoosePixelFormat(dc, &desc);
  if (!format) 
  {
    printf("Cannot choose OpenGL pixel format for dummy window!");
  }

  int ok = DescribePixelFormat(dc, format, sizeof(desc), &desc);
  Assert(ok && "Failed to describe OpenGL pixel format");

  // reason to create dummy window is that SetPixelFormat can be called only once for the window
  if (!SetPixelFormat(dc, format, &desc))
  {
    printf("Cannot set OpenGL pixel format for dummy window!");
  }

  HGLRC rc = wglCreateContext(dc);
  Assert(rc && "Failed to create OpenGL context for dummy window");

  ok = wglMakeCurrent(dc, rc);
  Assert(ok && "Failed to make current OpenGL context for dummy window");

  {
    //
    // Load Webgl extensions
    //
  }

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(rc);
  ReleaseDC(dummy, dc);
  DestroyWindow(dummy);
}