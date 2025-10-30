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
      Matrix s = MatrixScale(1.0f, 1.0f, 1.0f);
      // Matrix mult is not commutative. Careful with transforms...
      p.models[i * p.columnSize + j].transform = MatrixMultiply(t, s);
    }
  }

  return p;
}

void DrawPlaneView(PlaneView plane, float *mapHeight) {
  for (int i = 0; i < plane.rowSize; i++) {
    for (int j = 0; j < plane.columnSize; j++) {
      Model *m = &plane.models[i * plane.columnSize + j];
      float height = mapHeight[i * plane.columnSize + j];
      m->transform.m13 = Lerp(m->transform.m13, height, 0.1f);
      DrawModelWires(*m, ORIGIN, 1.0f, WHITE);
    }
  }
}

float *GetHeightMap(int rowSize, int columnSize) {
  float *height = calloc(rowSize * columnSize, sizeof(float));

  for (int i = 0; i < rowSize; i++) {
    for (int j = 0; j < columnSize; j++) {
      height[i * columnSize + j] = (float)GetRandomValue(-200, 200) / 1000.0f;
    }
  }

  return height;
}

int main(void) {
  InitWindow(1280, 720, "untitled.game");
  SetTargetFPS(60);

  PlaneView plane = GeneratePlaneView();
  float *heightMap = GetHeightMap(plane.rowSize, plane.columnSize);

  Camera3D camera = {0};
  camera.position = (Vector3){-10.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 15.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLANK);
    BeginMode3D(camera);
    if (IsKeyDown(KEY_SPACE)) {
      heightMap = GetHeightMap(plane.rowSize, plane.columnSize);
    }
    DrawPlaneView(plane, heightMap);
    // UpdateCamera(&camera, CAMERA_FREE);

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
