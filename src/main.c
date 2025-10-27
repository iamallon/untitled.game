#include "camera.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

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

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLANK);
    Begin3D();

    pos = Vector3Add(pos, HandleInput(10));
    DrawGrid(40, 10);
    DrawCube(pos, 10, 10, 10, WHITE);

    End3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
