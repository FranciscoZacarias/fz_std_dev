// Booleans and types
#define GL_FALSE 0
#define GL_TRUE  1

typedef u32 GLenum;
typedef f32 GLfloat;
typedef u32 GLbitfield;
typedef u32 GLuint;
typedef s32 GLint;
typedef s32 GLsizei;
typedef char GLchar;
typedef unsigned char GLboolean;

#if ARCH_ADDRSIZE == 64
typedef s64 GLsizeiptr;
typedef s64 GLintptr;
#elif ARCH_ADDRSIZE == 32
typedef s32 GLsizeiptr;
typedef s32 GLintptr;
#else
# error unhandled address size
#endif

// Primitive types
#define GL_POINTS         0x0000
#define GL_LINES          0x0001
#define GL_TRIANGLES      0x0004
#define GL_TRIANGLE_STRIP 0x0005

// Shader types and progrma info
#define GL_VERTEX_SHADER   0x8B31
#define GL_FRAGMENT_SHADER 0x8B30

#define GL_COMPILE_STATUS  0x8B81
#define GL_LINK_STATUS     0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84

// Buffer types and usage
#define GL_ARRAY_BUFFER         0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

#define GL_STATIC_DRAW  0x88E4
#define GL_DYNAMIC_DRAW 0x88E8

// Texture types
#define GL_TEXTURE_2D            0x0DE1
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100

// Texture parameters
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S     0x2802
#define GL_TEXTURE_WRAP_T     0x2803

#define GL_NEAREST 0x2600
#define GL_LINEAR  0x2601

#define GL_REPEAT           0x2901
#define GL_CLAMP_TO_EDGE    0x812F
#define GL_MIRRORED_REPEAT  0x8370

// Texture fomats
#define GL_RED    0x1903
#define GL_RG     0x8227
#define GL_RGB    0x1907
#define GL_RGBA   0x1908

#define GL_R8     0x8229
#define GL_RG8    0x822B
#define GL_RGB8   0x8051
#define GL_RGBA8  0x8058

#define GL_RGBA16F 0x881A
#define GL_RGBA32F 0x8814
#define GL_RGB16F  0x881B
#define GL_RGB32F  0x8815

#define GL_SRGB8        0x8C41
#define GL_SRGB8_ALPHA8 0x8C43

// Pixel types
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FLOAT         0x1406

// Blending
#define GL_BLEND              0x0BE2
#define GL_FUNC_ADD           0x8006
#define GL_FUNC_SUBTRACT      0x800A
#define GL_FUNC_REVERSE_SUBTRACT 0x800B

#define GL_SRC_ALPHA          0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE                1
#define GL_ZERO               0

// Framebuffers
#define GL_FRAMEBUFFER        0x8D40
#define GL_READ_FRAMEBUFFER   0x8CA8
#define GL_DRAW_FRAMEBUFFER   0x8CA9

#define GL_COLOR_ATTACHMENT0  0x8CE0
#define GL_DEPTH_ATTACHMENT   0x8D00
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A

#define GL_FRAMEBUFFER_COMPLETE 0x8CD5

#define GL_DEPTH_BUFFER_BIT   0x00000100
#define GL_COLOR_BUFFER_BIT   0x00004000
#define GL_STENCIL_BUFFER_BIT 0x00000400

// Debug
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_DEBUG_LOGGED_MESSAGES          0x9145
#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_DEBUG_GROUP_STACK_DEPTH        0x826D
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB   0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_ARB    0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB  0x8245
#define GL_DEBUG_SOURCE_API_ARB           0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB   0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB   0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB         0x824B
#define GL_DEBUG_TYPE_ERROR_ARB           0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB 0x824E
#define GL_DEBUG_TYPE_PORTABILITY_ARB     0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_ARB     0x8250
#define GL_DEBUG_TYPE_OTHER_ARB           0x8251
#define GL_DEBUG_LOGGED_MESSAGES_ARB      0x9145
#define GL_DEBUG_SEVERITY_HIGH_ARB        0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB      0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB         0x9148

// Misc
#define GL_NO_ERROR          0
#define GL_INVALID_ENUM      0x0500
#define GL_INVALID_VALUE     0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_OUT_OF_MEMORY     0x0505
