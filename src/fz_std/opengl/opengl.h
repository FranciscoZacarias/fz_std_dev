#ifndef OS_OPENGL_H
#define OS_OPENGL_H

#pragma comment(lib, "opengl32.lib")

function b32 os_opengl_init(); /* Initializes opengl context */

function void APIENTRY _os_opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user); /* Opengl debug callback */
function void          _os_opengl_load_functions();                                                                                                                /* Loads opengl functions */
function void          _os_opengl_get_webgl_functions();                                                                                                           /* Opens webgl functions */

#endif // OS_OPENGL_H