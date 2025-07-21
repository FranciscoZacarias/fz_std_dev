#ifndef FZ_MATH_H
#define FZ_MATH_H

#define PI 3.14159265358979323846f
#define EPSILON 0.000001f

#define Degrees(r) (r * (180 / PI))
#define Radians(d) (d * (PI / 180))

// @Section: Vec2
typedef union Vec2U16 { U16 data[2]; struct { U16 x, y; }; } Vec2U16;
#define vec2u16(x,y) ((Vec2U16){x,y})

typedef union Vec2U32 { U32 data[2]; struct { U32 x, y; }; } Vec2U32;
#define vec2u32(x,y) ((Vec2U32){x,y})

typedef union Vec2U64 { U64 data[2]; struct { U64 x, y; }; } Vec2U64;
#define vec2u64(x,y) ((Vec2U64){x,y})

typedef union Vec2S16 { S16 data[2]; struct { S16 x, y; }; } Vec2S16;
#define vec2s16(x,y) ((Vec2S16){x,y})

typedef union Vec2S32 { S32 data[2]; struct { S32 x, y; }; } Vec2S32;
#define vec2s32(x,y) ((Vec2S32){x,y})

typedef union Vec2S64 { S64 data[2]; struct { S64 x, y; }; } Vec2S64;
#define vec2s64(x,y) ((Vec2S64){x,y})

typedef union Vec2F32 { F32 data[2]; struct { F32 x, y; }; } Vec2F32;
#define vec2f32(x,y) ((Vec2F32){x,y})

typedef union Vec2F64 { F64 data[2]; struct { F64 x, y; }; } Vec2F64;
#define vec2f64(x,y) ((Vec2F64){x,y})


// @Section: Vec3
typedef union Vec3U16 { U16 data[3]; struct { U16 x, y, z; }; } Vec3U16;
#define vec3u16(x,y,z) ((Vec3U16){x,y,z})

typedef union Vec3U32 { U32 data[3]; struct { U32 x, y, z; }; } Vec3U32;
#define vec3u32(x,y,z) ((Vec3U32){x,y,z})

typedef union Vec3U64 { U64 data[3]; struct { U64 x, y, z; }; } Vec3U64;
#define vec3u64(x,y,z) ((Vec3U64){x,y,z})

typedef union Vec3S16 { S16 data[3]; struct { S16 x, y, z; }; } Vec3S16;
#define vec3s16(x,y,z) ((Vec3S16){x,y,z})

typedef union Vec3S32 { S32 data[3]; struct { S32 x, y, z; }; } Vec3S32;
#define vec3s32(x,y,z) ((Vec3S32){x,y,z})

typedef union Vec3S64 { S64 data[3]; struct { S64 x, y, z; }; } Vec3S64;
#define vec3s64(x,y,z) ((Vec3S64){x,y,z})

typedef union Vec3F32 { F32 data[3]; struct { F32 x, y, z; }; } Vec3F32;
#define vec3f32(x,y,z) ((Vec3F32){x,y,z})

typedef union Vec3F64 { F64 data[3]; struct { F64 x, y, z; }; } Vec3F64;
#define vec3f64(x,y,z) ((Vec3F64){x,y,z})


// @Section: Vec4
typedef union Vec4U16 { U16 data[4]; struct { U16 x, y, z, w; }; } Vec4U16;
#define vec4u16(x,y,z,w) ((Vec4U16){x,y,z,w})

typedef union Vec4U32 { U32 data[4]; struct { U32 x, y, z, w; }; } Vec4U32;
#define vec4u32(x,y,z,w) ((Vec4U32){x,y,z,w})

typedef union Vec4U64 { U64 data[4]; struct { U64 x, y, z, w; }; } Vec4U64;
#define vec4u64(x,y,z,w) ((Vec4U64){x,y,z,w})

typedef union Vec4S16 { S16 data[4]; struct { S16 x, y, z, w; }; } Vec4S16;
#define vec4s16(x,y,z,w) ((Vec4S16){x,y,z,w})

typedef union Vec4S32 { S32 data[4]; struct { S32 x, y, z, w; }; } Vec4S32;
#define vec4s32(x,y,z,w) ((Vec4S32){x,y,z,w})

typedef union Vec4S64 { S64 data[4]; struct { S64 x, y, z, w; }; } Vec4S64;
#define vec4s64(x,y,z,w) ((Vec4S64){x,y,z,w})

typedef union Vec4F32 { F32 data[4]; struct { F32 x, y, z, w; }; } Vec4F32;
#define vec4f32(x,y,z,w) ((Vec4F32){x,y,z,w})

typedef union Vec4F64 { F64 data[4]; struct { F64 x, y, z, w; }; } Vec4F64;
#define vec4f64(x,y,z,w) ((Vec4F64){x,y,z,w})


// @Section: Matrix
typedef union Mat4F32 {
  F32 data[4][4];
  struct {
    F32 m0, m4, m8,  m12,
        m1, m5, m9,  m13,
        m2, m6, m10, m14,
        m3, m7, m11, m15;
  };
} Mat4F32;
#define mat4f32(diag) (Mat4F32) {diag,0.0f,0.0f,0.0f,0.0f,diag,0.0f,0.0f,0.0f,0.0f,diag,0.0f,0.0f,0.0f,0.0f,diag}
#define mat4f32_identity() mat4f32(1.0f)

// @Section: Quaternion
typedef union QuatF32 {
  F32 data[4];
  struct {
    F32 x;
    F32 y;
    F32 z;
    F32 w;
  };
} QuatF32;
#define quatf32(x,y,z,w) (QuatF32){x,y,z,w}
#define quatf32_identity() quatf32(0.0f, 0.0f, 0.0f, 1.0f)

// @Section: Transform
typedef struct TransformF32 {
  Vec3F32 translation;
  QuatF32 rotation;
  Vec3F32 scale;
} TransformF32;
#define transformf32(t,r,s) (TransformF32){t,r,s}

// @Section: 1D Range
typedef union Range1U32 {
  F32 data[2];
  struct {
    U32 min;
    U32 max;
  };
} Range1U32;

typedef union Range1U64 {
  F32 data[2];
  struct {
    U64 min;
    U64 max;
  };
} Range1U64;

typedef union Range1S32 {
  F32 data[2];
  struct {
    S32 min;
    S32 max;
  };
} Range1S32;

typedef union Range1S64 {
  F32 data[2];
  struct {
    S64 min;
    S64 max;
  };
} Range1S64;

typedef union Range1F32 {
  F32 data[2];
  struct {
    F32 min;
    F32 max;
  };
} Range1F32;

typedef union Range1F64 {
  F32 data[2];
  struct {
    F64 min;
    F64 max;
  };
} Range1F64;

// @Section: 2D Range
typedef union Range2U32 {
  struct {
    Vec2U32 min;
    Vec2U32 max;
  };
  struct {
    Vec2U32 p0;
    Vec2U32 p1;
  };
  struct {
    U32 x0, y0;
    U32 x1, y1;
  };
  Vec2U32 v[2];
} Range2U32;

typedef union Range2U64 {
  struct {
    Vec2U64 min;
    Vec2U64 max;
  };
  struct {
    Vec2U64 p0;
    Vec2U64 p1;
  };
  struct {
    U64 x0, y0;
    U64 x1, y1;
  };
  Vec2U64 v[2];
} Range2U64;

typedef union Range2S32 {
  struct {
    Vec2S32 min;
    Vec2S32 max;
  };
  struct {
    Vec2S32 p0;
    Vec2S32 p1;
  };
  struct {
    S32 x0, y0;
    S32 x1, y1;
  };
  Vec2S32 v[2];
} Range2S32;

typedef union Range2S64 {
  struct {
    Vec2S64 min;
    Vec2S64 max;
  };
  struct {
    Vec2S64 p0;
    Vec2S64 p1;
  };
  struct {
    S64 x0, y0;
    S64 x1, y1;
  };
  Vec2S64 v[2];
} Range2S64;

typedef union Range2F32 {
  struct {
    Vec2F32 min;
    Vec2F32 max;
  };
  struct {
    Vec2F32 p0;
    Vec2F32 p1;
  };
  struct {
    F32 x0, y0;
    F32 x1, y1;
  };
  Vec2F32 v[2];
} Range2F32;

typedef union Range2F64 {
  struct {
    Vec2F64 min;
    Vec2F64 max;
  };
  struct {
    Vec2F64 p0;
    Vec2F64 p1;
  };
  struct {
    F64 x0, y0;
    F64 x1, y1;
  };
  Vec2F64 v[2];
} Range2F64;

// TODO(Fz): Colors should not be here, I think.
#define Color_Red        vec4f32(1.0f,  0.0f,  0.0f,  1.0f)
#define Color_Green      vec4f32(0.0f,  1.0f,  0.0f,  1.0f)
#define Color_Blue       vec4f32(0.0f,  0.0f,  1.0f,  1.0f)
#define Color_Yellow     vec4f32(1.0f,  1.0f,  0.0f,  1.0f)
#define Color_Cyan       vec4f32(0.0f,  1.0f,  1.0f,  1.0f)
#define Color_Magenta    vec4f32(1.0f,  0.0f,  1.0f,  1.0f)
#define Color_White      vec4f32(1.0f,  1.0f,  1.0f,  1.0f)
#define Color_Black      vec4f32(0.0f,  0.0f,  0.0f,  1.0f)
#define Color_Gray       vec4f32(0.5f,  0.5f,  0.5f,  1.0f)
#define Color_LightGray  vec4f32(0.75f, 0.75f, 0.75f, 1.0f)
#define Color_DarkGray   vec4f32(0.25f, 0.25f, 0.25f, 1.0f)
#define Color_Orange     vec4f32(1.0f,  0.5f,  0.0f,  1.0f)
#define Color_Purple     vec4f32(0.5f,  0.0f,  0.5f,  1.0f)
#define Color_Brown      vec4f32(0.6f,  0.4f,  0.2f,  1.0f)
#define Color_Pink       vec4f32(1.0f,  0.75f, 0.8f,  1.0f)

#define AXIS_X vec3f32(1.0f, 0.0f, 0.0f)
#define AXIS_Y vec3f32(0.0f, 1.0f, 0.0f)
#define AXIS_Z vec3f32(0.0f, 0.0f, 1.0f)

internal F32 f32_min(F32 a, F32 b);
internal F32 f32_max(F32 a, F32 b);
internal F32 f32_abs(F32 value);
internal F32 f32_lerp(F32 start, F32 end, F32 amount);
internal F32 f32_normalize(F32 value, F32 start, F32 end);
internal F32 f32_remap(F32 value, F32 inputStart, F32 inputEnd, F32 outputStart, F32 outputEnd);
internal F32 f32_wrap(F32 value, F32 min, F32 max);

// TODO(fz): Rename functions to match their type E,g, vec2f32_distance -> vec2f32_distance
internal F32 vec2f32_distance(Vec2F32 a, Vec2F32 b);
internal F32 vec2f32_distance_signed(Vec2F32 a, Vec2F32 b, Vec2F32 reference);

internal Vec2F32 vec2f32_add(Vec2F32 a, Vec2F32 b);
internal Vec2F32 vec2f32_sub(Vec2F32 a, Vec2F32 b);
internal Vec2F32 vec2f32_scale(Vec2F32 v, F32 scalar);
internal Vec2F32 vec2f32_normalize(Vec2F32 v);
internal F32 vec2f32_dot(Vec2F32 a, Vec2F32 b);
internal F32 vec2f32_length(Vec2F32 v);

internal Vec3F32 vec3f32_from_vec4f32(Vec4F32 v); /* Discards the w value */

internal Vec3F32 vec3f32_add(Vec3F32 a, Vec3F32 b);
internal Vec3F32 vec3f32_sub(Vec3F32 a, Vec3F32 b);
internal Vec3F32 vec3f32_mul(Vec3F32 a, Vec3F32 b);
internal Vec3F32 vec3f32_div(Vec3F32 a, Vec3F32 b);

internal Vec3F32 vec3f32_cross(Vec3F32 a, Vec3F32 b);
internal Vec3F32 vec3f32_scale(Vec3F32 v, F32 scalar);
internal Vec3F32 vec3f32_scale_xyz(Vec3F32 v, F32 scale_x, F32 scale_y, F32 scale_z);
internal Vec3F32 vec3f32_normalize(Vec3F32 v);
internal Vec3F32 vec3f32_rotate_by_axis(Vec3F32 v, Vec3F32 axis, F32 angle);
internal Vec3F32 vec3f32_lerp(Vec3F32 a, Vec3F32 b, F32 t);
internal Vec3F32 vec3f32_unproject(Vec3F32 source, Mat4F32 projection, Mat4F32 view);
internal Vec3F32 mat4f32_transform_vec3f32(Mat4F32 mat, Vec3F32 vec);

internal F32 vec3f32_dot(Vec3F32 a, Vec3F32 b);
internal F32 vec3f32_length(Vec3F32 v);
internal F32 vec3f32_distance(Vec3F32 a, Vec3F32 b);
internal F32 vec3f32_angle(Vec3F32 a, Vec3F32 b);

internal Vec4F32 vec4f32_from_vec3f32(Vec3F32 v);

internal Vec4F32 vec4f32_add(Vec4F32 a, Vec4F32 b);
internal Vec4F32 vec4f32_sub(Vec4F32 a, Vec4F32 b);
internal Vec4F32 vec4f32_mul(Vec4F32 a, Vec4F32 b);
internal Vec4F32 vec4f32_div(Vec4F32 a, Vec4F32 b);
internal Vec4F32 vec4f32_mul_mat4f32(Vec4F32 v, Mat4F32 m);

internal Vec4F32 vec4f32_scale(Vec4F32 v, F32 scalar);
internal Vec4F32 vec4f32_normalize(Vec4F32 v);
internal Vec4F32 vec4f32_lerp(Vec4F32 a, Vec4F32 b, F32 t);

internal F32 vec4f32_dot(Vec4F32 a, Vec4F32 b);
internal F32 vec4f32_length(Vec4F32 v);
internal F32 vec4f32_distance(Vec4F32 a, Vec4F32 b);

internal Mat4F32 mat4f32_mul(Mat4F32 left, Mat4F32 right); /* Apply the left matrix to the right matrix*/ 

internal Mat4F32 mat4f32_translate(F32 x, F32 y, F32 z);
internal Mat4F32 mat4f32_rotate_axis(Vec3F32 axis, F32 radians);
internal Mat4F32 mat4f32_rotate_x(F32 radians);
internal Mat4F32 mat4f32_rotate_y(F32 radians);
internal Mat4F32 mat4f32_rotate_z(F32 radians);
internal Mat4F32 mat4f32_rotate_xyz(Vec3F32 radians);
internal Mat4F32 mat4f32_rotate_zyx(Vec3F32 radians);

internal Mat4F32 mat4f32_transpose(Mat4F32 m);
internal Mat4F32 mat4f32_scale(F32 x, F32 y, F32 z);
internal Mat4F32 mat4f32_frustum(F64 left, F64 right, F64 bottom, F64 top, F64 near_plane, F64 far_plane);
internal Mat4F32 mat4f32_perspective(F32 fovy, F32 window_width, F32 window_height, F32 near_plane, F32 far_plane);
internal Mat4F32 mat4f32_ortographic(F64 left, F64 right, F64 bottom, F64 top, F64 near_plane, F64 far_plane);
internal Mat4F32 mat4f32_look_at(Vec3F32 eye, Vec3F32 target, Vec3F32 up);
internal Mat4F32 mat4f32_from_quatf32(QuatF32 q);
internal TransformF32 transformf32_from_mat4f32(Mat4F32 mat);

internal QuatF32 quatf32_add(QuatF32 q1, QuatF32 q2);
internal QuatF32 quatf32_add_value(QuatF32 q, F32 value);
internal QuatF32 quatf32_subtract(QuatF32 q1, QuatF32 q2);
internal QuatF32 quatf32_subtract_value(QuatF32 q, F32 value);
internal F32     quatf32_length(QuatF32 q);
internal QuatF32 quatf32_normalize(QuatF32 q);
internal QuatF32 quatf32_invert(QuatF32 q);
internal QuatF32 quatf32_multiply(QuatF32 q1, QuatF32 q2);
internal QuatF32 quatf32_scale(QuatF32 q, F32 scalar);
internal QuatF32 quatf32_divide(QuatF32 q1, QuatF32 q2);
internal QuatF32 quatf32_lerp(QuatF32 q1, QuatF32 q2, F32 amount);
internal QuatF32 quatf32_nlerp(QuatF32 q1, QuatF32 q2, F32 amount);
internal QuatF32 quatf32_slerp(QuatF32 q1, QuatF32 q2, F32 amount);
internal QuatF32 quatf32_cubic_hermit_spline(QuatF32 q1, QuatF32 outTangent1, QuatF32 q2, QuatF32 inTangent2, F32 t);
internal QuatF32 quatf32_from_vec3f32_to_vec3f32(Vec3F32 from, Vec3F32 to);
internal QuatF32 quatf32_from_mat4f32(Mat4F32 mat);
internal QuatF32 quatf32_from_axis_angle(Vec3F32 axis, F32 angle);
internal void    axis_angle_from_quatf32(QuatF32 q, Vec3F32 *axis, F32 *angle);
internal QuatF32 quatf32_from_euler(F32 pitch, F32 yaw, F32 roll);
internal void    euler_from_quatf32(QuatF32 q, F32* pitch, F32* yaw, F32* roll);
internal QuatF32 quatf32_mul_mat4f32(QuatF32 q, Mat4F32 mat);
internal B32     quatf32_equals(QuatF32 p, QuatF32 q);
internal Vec3F32 quatf32_rotate_vec3f32(QuatF32 q, Vec3F32 v);
internal QuatF32 quatf32_conjugate(QuatF32 q);
internal F32     quatf32_dot(QuatF32 q1, QuatF32 q2);

///////////////////////
//~ Prints

internal void vec2f32_print(Vec2F32 v, const U8 *label);
internal void vec3f32_print(Vec3F32 v, const U8 *label);
internal void vec4f32_print(Vec4F32 v, const U8 *label);
internal void mat4f32_print(Mat4F32 m, const U8 *label);
internal void quatf32_print(QuatF32 q, const U8 *label);
internal void transformf32_print(TransformF32 t, const U8 *label);

#endif // FZ_MATH_H