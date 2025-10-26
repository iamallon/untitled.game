#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

Camera3D GetCamera(void) {
  Camera3D camera = {0};
  camera.position = (Vector3){45.0f, 45.0f, 45.0f};
  camera.target = (Vector3){0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 75.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;

  return camera;
}

Vector3 HandleInput(float size) {
  int key = GetKeyPressed();
  if (key != 0) {
    if (key == KEY_RIGHT) {
      return (Vector3){0, 0, size};
    }
    if (key == KEY_LEFT) {
      return (Vector3){0, 0, -size};
    }
    if (key == KEY_UP) {
      return (Vector3){size, 0, 0};
    }
    if (key == KEY_DOWN) {
      return (Vector3){-size, 0, 0};
    }
  }

  return (Vector3){0};
}

int main(void) {
  InitWindow(1280, 720, "untitled.game");
  SetTargetFPS(60);

  Vector3 pos = {5, 5, 5};
  Camera3D camera = GetCamera();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode3D(camera);

    UpdateCamera(&camera, CAMERA_FREE);

    pos = Vector3Add(pos, HandleInput(10));
    DrawGrid(40, 10);
    DrawCube(pos, 10, 10, 10, BLACK);

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
