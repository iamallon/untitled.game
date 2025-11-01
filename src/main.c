#include "plane.h"
#include "raylib.h"
#include "raymath.h"

#define VIEW_ROWS 4
#define VIEW_COLUMNS 4
#define GRAVITY 9.8f
#define PLAYER_VELOCITY 3.0f

Vector3 GetPosition(Matrix m) { return (Vector3){m.m12, m.m13, m.m14}; }

void ApplyPhysics(PlaneView p, Model *m) {
  PlaneCollision col = GetWheelPlaneCollision(p, GetPosition(m->transform));

  if (col.collision.hit && col.collision.distance > 0.8f) {
    m->transform = MatrixMultiply(
        m->transform, MatrixTranslate(0, -GRAVITY * GetFrameTime(), 0));
  }
}

int main(void) {
  int currentMonitor = GetCurrentMonitor();
  InitWindow(GetMonitorWidth(currentMonitor), GetMonitorHeight(currentMonitor),
             "untitled.game");
  SetTargetFPS(GetMonitorRefreshRate(currentMonitor));

  Model player = LoadModelFromMesh(GenMeshSphere(0.8f, 20, 20));
  player.transform = MatrixTranslate(0, 10, 0);
  PlaneView plane = GeneratePlaneView(VIEW_ROWS, VIEW_COLUMNS);
  HeightMap map = GetHeightMap(200, 200);

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

    if (IsKeyDown(KEY_K)) {
      player.transform = MatrixMultiply(
          player.transform,
          MatrixTranslate(0, 0, -PLAYER_VELOCITY * GetFrameTime()));
    }
    if (IsKeyDown(KEY_J)) {
      player.transform = MatrixMultiply(
          player.transform,
          MatrixTranslate(0, 0, PLAYER_VELOCITY * GetFrameTime()));
    }
    if (IsKeyDown(KEY_H)) {
      player.transform = MatrixMultiply(
          player.transform,
          MatrixTranslate(-PLAYER_VELOCITY * GetFrameTime(), 0, 0));
    }
    if (IsKeyDown(KEY_L)) {
      player.transform = MatrixMultiply(
          player.transform,
          MatrixTranslate(PLAYER_VELOCITY * GetFrameTime(), 0, 0));
    }

    DrawModelWires(player, ORIGIN, 1.0f, WHITE);
    PlaneCollision col =
        GetWheelPlaneCollision(plane, GetPosition(player.transform));

    ApplyPhysics(plane, &player);

    DrawPlaneView(&plane, map);
    UpdateCamera(&camera, CAMERA_FREE);

    EndMode3D();
    DrawFPS(10, 10);
    DrawText(TextFormat("X: %d Y: %d", plane.offset.column, plane.offset.row),
             10, 50, 50, WHITE);
    DrawText(TextFormat("Distance: %f, X: %f, Z: %f", col.collision.distance,
                        col.collision.point.x, col.collision.point.z),
             10, 100, 50, WHITE);
    DrawText(TextFormat("Player: X:%f, Y:%f, Z:%f", player.transform.m12,
                        player.transform.m13, player.transform.m14),
             10, 150, 50, WHITE);
    DrawText(TextFormat("Height: %f", GetHeightFromMap(map, plane.offset,
                                                       col.collision.point.z,
                                                       col.collision.point.x)),
             10, 200, 50, WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
