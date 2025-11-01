#include "car.h"
#include "physics.h"
#include "plane.h"
#include "raylib.h"
#include "raymath.h"

#define VIEW_ROWS 16
#define VIEW_COLUMNS 16
#define PLAYER_VELOCITY 3.0f

int main(void) {
  int currentMonitor = GetCurrentMonitor();
  InitWindow(GetMonitorWidth(currentMonitor), GetMonitorHeight(currentMonitor),
             "untitled.game");
  SetTargetFPS(GetMonitorRefreshRate(currentMonitor));

  Image image = LoadImage("../res/tiles.jpg");
  Texture2D texture = LoadTextureFromImage(image);

  PlaneView plane = GeneratePlaneView(VIEW_ROWS, VIEW_COLUMNS, texture);
  HeightMap map = GetHeightMap(200, 200);

  Car car = GenerateCar(LoadModelFromMesh(GenMeshCube(1, 1, 1)));

  Camera3D camera = {0};
  camera.position = (Vector3){-10.0f, 10.0f, 10.0f};
  camera.target = (Vector3){8, 0, 0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 20.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLANK);
    BeginMode3D(camera);

    if (IsKeyPressed(KEY_DOWN)) {
      plane.offset.row = Clamp(plane.offset.row + 1, 0, map.rowSize);
    }
    if (IsKeyPressed(KEY_UP)) {
      plane.offset.row = Clamp(plane.offset.row - 1, 0, map.rowSize);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      plane.offset.column = Clamp(plane.offset.column + 1, 0, map.columnSize);
    }
    if (IsKeyPressed(KEY_LEFT)) {
      plane.offset.column = Clamp(plane.offset.column - 1, 0, map.columnSize);
    }

    DrawCar(car);
    DrawPlaneView(&plane, map);
    ApplyCarPhysics(plane, &car);
    ApplyCarInput(plane, &car);

    UpdateCamera(&camera, CAMERA_FREE);

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
