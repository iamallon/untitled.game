#include "plane.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

PlaneView GeneratePlaneView(int rowSize, int columnSize, Texture texture) {
  PlaneView p = {0};
  p.rowSize = rowSize;
  p.columnSize = columnSize;
  p.models = calloc(p.rowSize * p.columnSize, sizeof(Model));
  for (int i = 0; i < p.rowSize; i++) {
    for (int j = 0; j < p.columnSize; j++) {
      p.models[i * p.columnSize + j] = LoadModelFromMesh(GenMeshCube(1, 1, 1));
      p.models[i * p.columnSize + j].transform = MatrixTranslate(j, 0, i);
      SetMaterialTexture(&p.models[i * p.columnSize + j].materials[0],
                         MATERIAL_MAP_DIFFUSE, texture);
    }
  }

  return p;
}

// There is a  buffer overflow here for the HeightMap
// because of the offsetX and offsetY;
void DrawPlaneView(PlaneView *plane, HeightMap map) {
  for (int i = 0; i < plane->rowSize; i++) {
    for (int j = 0; j < plane->columnSize; j++) {
      Model *m = &plane->models[i * plane->columnSize + j];
      float height = GetHeightFromMap(map, plane->offset, i, j);

      // Apply transform on Y axis.
      m->transform.m13 = Lerp(m->transform.m13, height, 0.1f);
      DrawModel(*m, ORIGIN, 1.0f, WHITE);
    }
  }
}

PlaneCollision GetPlaneCollision(PlaneView plane, Vector3 origin) {
  Ray ray = {0};
  ray.position = origin;
  ray.direction = VECTOR_DOWN;

  DrawRay(ray, RED);

  for (int i = 0; i < plane.rowSize; i++) {
    for (int j = 0; j < plane.columnSize; j++) {
      Model tile = plane.models[i * plane.columnSize + j];
      RayCollision col = GetRayCollisionBox(ray, GetModelBoundingBox(tile));
      if (col.hit) {
        col.point = (Vector3){j, col.point.y, i};
        return (PlaneCollision){col, tile};
      }
    }
  }

  return (PlaneCollision){0};
}

HeightMap GetHeightMap(int rowSize, int columnSize) {
  HeightMap m = {0};
  m.rowSize = rowSize;
  m.columnSize = columnSize;
  m.heights = calloc(rowSize * columnSize, sizeof(float));

  for (int i = 0; i < rowSize; i++) {
    for (int j = 0; j < columnSize; j++) {
      m.heights[i * columnSize + j] =
          (float)GetRandomValue(-200, 200) / 1000.0f;
    }
  }

  return m;
}

float GetHeightFromMap(HeightMap map, Offset offset, int row, int column) {
  row = Clamp(row, 0, map.columnSize);
  column = Clamp(column, 0, map.rowSize);
  return map
      .heights[(row + offset.row) * map.columnSize + column + offset.column];
}
