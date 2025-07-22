internal void camera_init(Camera* camera, Vec3F32 position, Vec3F32 look_at, f32 speed, f32 sensitivity) {
  AssertNoReentry();
    
  camera->position    = vec3f32(0.0f, 0.0f, 5.0f);
  camera->orientation = quatf32_identity();
  camera->fov         = 90.0f;
  camera->speed       = speed;
  camera->sensitivity = sensitivity;
  camera->mode        = CameraMode_Select;
}

internal void camera_update(Camera* camera, f32 delta_time) {
  local_persist b32 was_right_mouse_button_down = 0;

  if (input_is_button_down(MouseButton_Right)) {
    if (!was_right_mouse_button_down) {
      _InputState.mouse_previous.screen_space_x = _InputState.mouse_current.screen_space_x;
      _InputState.mouse_previous.screen_space_y = _InputState.mouse_current.screen_space_y;
      was_right_mouse_button_down = 1;
      win32_lock_cursor(true);
      win32_hide_cursor(true);
    }

    camera->mode = CameraMode_Fly;

    f32 camera_speed = (f32)(camera->speed * delta_time);

    Vec3F32 forward = camera_get_forward(camera);
    Vec3F32 right   = camera_get_right(camera);
    Vec3F32 up      = camera_get_up(camera);

    if (input_is_key_down(KeyboardKey_W)) camera->position = vec3f32_add(camera->position, vec3f32_scale(forward, camera_speed));
    if (input_is_key_down(KeyboardKey_S)) camera->position = vec3f32_sub(camera->position, vec3f32_scale(forward, camera_speed));
    if (input_is_key_down(KeyboardKey_D)) camera->position = vec3f32_add(camera->position, vec3f32_scale(right, camera_speed));
    if (input_is_key_down(KeyboardKey_A)) camera->position = vec3f32_sub(camera->position, vec3f32_scale(right, camera_speed));
    if (input_is_key_down(KeyboardKey_E)) camera->position = vec3f32_add(camera->position, vec3f32_scale(up, camera_speed));
    if (input_is_key_down(KeyboardKey_Q)) camera->position = vec3f32_sub(camera->position, vec3f32_scale(up, camera_speed));

    // Mouse look
    f32 sensitivity = 0.0015f;
    sensitivity *= camera->sensitivity;

    f32 dx = _InputState.mouse_current.delta_x;
    f32 dy = _InputState.mouse_current.delta_y;

    f32 yaw   = -dx * sensitivity;
    f32 pitch = -dy * sensitivity;

    QuatF32 yaw_rotation   = quatf32_from_axis_angle((Vec3F32){0.0f, 1.0f, 0.0f}, yaw);
    Vec3F32 camera_right   = camera_get_right(camera);
    QuatF32 pitch_rotation = quatf32_from_axis_angle(camera_right, pitch);

    camera->orientation = quatf32_multiply(yaw_rotation, quatf32_multiply(pitch_rotation, camera->orientation));
    camera->orientation = quatf32_normalize(camera->orientation);

    RECT rect;
    GetClientRect(_WindowHandle, &rect);
    POINT center = {(rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2};
    ClientToScreen(_WindowHandle, &center);
    SetCursorPos(center.x, center.y);

    // Manually set current mouse position to center (so next frame delta is correct)
    _InputState.mouse_current.screen_space_x = (f32)((rect.right - rect.left) / 2);
    _InputState.mouse_current.screen_space_y = (f32)((rect.bottom - rect.top) / 2);
  } else {
    camera->mode = CameraMode_Select;
    was_right_mouse_button_down = 0;
    win32_lock_cursor(false);
    win32_hide_cursor(false);
  }
}

internal Vec3F32 camera_get_forward(Camera* camera) {
  Mat4F32 rot     = mat4f32_from_quatf32(camera->orientation);
  Vec3F32 forward = {0.0f, 0.0f, -1.0f};
  return vec3f32_normalize(mat4f32_transform_vec3f32(rot, forward));
}

internal Vec3F32 camera_get_right(Camera* camera) {
  Mat4F32 rot   = mat4f32_from_quatf32(camera->orientation);
  Vec3F32 right = {1.0f, 0.0f, 0.0f};
  return vec3f32_normalize(mat4f32_transform_vec3f32(rot, right));
}

internal Vec3F32 camera_get_up(Camera* camera) {
  Mat4F32 rot = mat4f32_from_quatf32(camera->orientation);
  Vec3F32 up  = {0.0f, 1.0f, 0.0f};
  return vec3f32_normalize(mat4f32_transform_vec3f32(rot, up));
}

internal Mat4F32 camera_get_view_matrix(Camera* camera) {
  Vec3F32 forward = camera_get_forward(camera);
  Vec3F32 up      = camera_get_up(camera);
  Vec3F32 target  = vec3f32_add(camera->position, forward);
  Mat4F32 result  = mat4f32_look_at(camera->position, target, up);
  return result;
}

internal void camera_look_at(Camera* camera, Vec3F32 target) {
  Vec3F32 direction   = vec3f32_normalize(vec3f32_sub(target, camera->position));
  Vec3F32 forward     = {0.0f, 0.0f, -1.0f};
  camera->orientation = quatf32_from_vec3f32_to_vec3f32(forward, direction);
}

internal void camera_set_euler(Camera* camera, f32 pitch, f32 yaw, f32 roll) {
  camera->orientation = quatf32_from_euler(pitch, yaw, roll);
}