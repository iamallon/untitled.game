#include "camera.h"
#include "raylib.h"
#include "raymath.h"

static Camera3D camera = {0};

void SetCamera(void) {
  camera.position = (Vector3){200.0f, 200.0f, 200.0f};
  camera.target = (Vector3){0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 75.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;
}

void Begin3D(void) {
  SetCamera();
  BeginMode3D(camera);
}

void End3D(void) { EndMode3D(); }
