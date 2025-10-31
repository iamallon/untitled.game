#include "plane.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

#define VIEW_ROWS 16
#define VIEW_COLUMNS 16

int main(void) {
  InitWindow(1280, 720, "untitled.game");
  SetTargetFPS(60);

  PlaneView plane = GeneratePlaneView(VIEW_ROWS, VIEW_COLUMNS);
  HeightMap map = GetHeightMap(200, 200);

  Camera3D camera = {0};
  camera.position = (Vector3){-10.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 15.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;

  Vector2 offset = {0};
  char offsetTextBuf[60];

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLANK);
    BeginMode3D(camera);

    if (IsKeyPressed(KEY_DOWN)) {
      offset.y = Clamp(offset.y + 1, 0, map.rowSize);
    }
    if (IsKeyPressed(KEY_UP)) {
      offset.y = Clamp(offset.y - 1, 0, map.rowSize);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      offset.x = Clamp(offset.x + 1, 0, map.columnSize);
    }
    if (IsKeyPressed(KEY_LEFT)) {
      offset.x = Clamp(offset.x - 1, 0, map.columnSize);
    }
    DrawPlaneView(plane, map, offset.x, offset.y);
    // UpdateCamera(&camera, CAMERA_FREE);

    sprintf(offsetTextBuf, "X: %f Y: %f", offset.x, offset.y);
    EndMode3D();
    DrawFPS(10, 10);
    DrawText(offsetTextBuf, 10, 50, 10, WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
