#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

#define ORIGIN (Vector3){0}
#define ROW_SIZE 16;
#define COLUMN_SIZE 16;

// What the fuck is wrong with unsigned int division;
typedef struct {
  int rowSize;
  int columnSize;
  Model *models;
} PlaneView;

static PlaneView GeneratePlaneView(void) {
  PlaneView p = {0};
  p.rowSize = ROW_SIZE;
  p.columnSize = COLUMN_SIZE;
  p.models = calloc(p.rowSize * p.columnSize, sizeof(Model));

  for (int i = 0; i < p.rowSize; i++) {
    for (int j = 0; j < p.columnSize; j++) {
      p.models[i * p.columnSize + j] = LoadModelFromMesh(GenMeshCube(1, 1, 1));
      Matrix t =
          MatrixTranslate(-(p.columnSize / 2) + j, 0, -(p.rowSize / 2) + i);
      Matrix s = MatrixScale(0.3f, 0.3f, 0.3f);
      p.models[i * p.columnSize + j].transform = MatrixMultiply(t, s);
    }
  }

  return p;
}

void DrawPlaneView(PlaneView plane, int *mapHeight) {
  for (int i = 0; i < plane.rowSize; i++) {
    for (int j = 0; j < plane.columnSize; j++) {
      Model *m = &plane.models[i * plane.columnSize + j];
      int height = mapHeight[i * plane.columnSize + j];
      m->transform.m13 = Lerp(m->transform.m13, height, 0.001f);
      DrawModelWires(*m, ORIGIN, 1.0f, WHITE);
    }
  }
}

int main(void) {
  InitWindow(1280, 720, "untitled.game");
  SetTargetFPS(60);

  PlaneView plane = GeneratePlaneView();

  int height[plane.rowSize * plane.columnSize];
  for (int i = 0; i < plane.rowSize; i++) {
    for (int j = 0; j < plane.columnSize; j++) {
      height[i * plane.columnSize + j] = GetRandomValue(-2, 2);
    }
  }

  Camera3D camera = {0};
  camera.position = (Vector3){-10.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 5.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLANK);
    BeginMode3D(camera);

    DrawPlaneView(plane, height);
    // UpdateCamera(&camera, CAMERA_FREE);

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
