#ifndef OS_OPENGL_H
#define OS_OPENGL_H

#pragma comment(lib, "opengl32.lib")

#include "external/glcorearb.h"

///////////////////////////////////////////////////////
// @Section: Define Opengl function pointers

typedef void (APIENTRYP PFNglUseProgramPROC) (GLuint program);
typedef void (APIENTRYP PFNglDebugMessageCallbackPROC) (GLDEBUGPROC callback, const void *userParam);


// #define GL_FUNC(ret,name,params) typedef ret name params;
// # include "opengl_functions.inl"
// #undef GL_FUNC

///////////////////////////////////////////////////////
// @Section: Generate Opengl function pointers

PFNglUseProgramPROC glUseProgram = NULL;
PFNglDebugMessageCallbackPROC glDebugMessageCallback = NULL;

// #define GL_FUNC(ret,name,params) global ret name = NULL;
// # include "opengl_functions.inl"
// #undef GL_FUNC

///////////////////////////////////////////////////////
// @Section: Opengl entry point
function b32 os_opengl_init(); /* Initializes opengl context */

///////////////////////////////////////////////////////
// @Section: Opengl helpers
function void APIENTRY _os_opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user); /* Opengl debug callback */
function b32           _os_opengl_load_functions();                                                                                                                /* Loads opengl function pointers */

#endif // OS_OPENGL_H