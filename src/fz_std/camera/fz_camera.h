#ifndef FZ_CAMERA_H
#define FZ_CAMERA_H

#ifndef FZ_STD_INCLUDED
# error fz_os_window.h requires including fz_std library. Please include fz_include.h before including this header.
#endif

#define WORLD_UP      vec3f32(0.0f, 1.0f,  0.0f)
#define WORLD_RIGHT   vec3f32(1.0f, 0.0f,  0.0f)
#define WORLD_FORWARD vec3f32(0.0f, 0.0f, -1.0f)

typedef enum Camera_Mode {
  CameraMode_Select,
  CameraMode_Fly,
  CameraMode_Disabled
} Camera_Mode;

typedef enum Camera_Movement {
  CameraMovement_Front,
  CameraMovement_Back,
  CameraMovement_Right,
  CameraMovement_Left,
  CameraMovement_Up,
  CameraMovement_Down
} Camera_Movement;

typedef struct Camera {
  Vec3F32 position;
  QuatF32 orientation;
  f32 fov;
  f32 speed;
  f32 sensitivity;
  Camera_Mode mode;
} Camera;

internal void    camera_init(Camera* camera, Vec3F32 position, Vec3F32 look_at, f32 speed, f32 sensitivity);
internal void    camera_update(Camera* camera, f32 delta_time);
internal Vec3F32 camera_get_forward(Camera* camera);
internal Vec3F32 camera_get_right(Camera* camera);
internal Vec3F32 camera_get_up(Camera* camera);
internal Mat4F32 camera_get_view_matrix(Camera* camera);
internal void    camera_look_at(Camera* camera, Vec3F32 target);
internal void    camera_set_euler(Camera* camera, f32 pitch, f32 yaw, f32 roll);

#endif // FZ_CAMERA_H