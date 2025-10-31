#include "plane.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

PlaneView GeneratePlaneView(int rowSize, int columnSize) {
  PlaneView p = {0};
  p.rowSize = rowSize;
  p.columnSize = columnSize;
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

// There is a  buffer overflow here for the HeightMap
// because of the offsetX and offsetY;
void DrawPlaneView(PlaneView plane, HeightMap map, int offsetX, int offsetY) {
  for (int i = 0; i < plane.rowSize; i++) {
    for (int j = 0; j < plane.columnSize; j++) {
      Model *m = &plane.models[i * plane.columnSize + j];
      float height =
          map.heights[((i + offsetY) * plane.columnSize) + j + offsetX];
      m->transform.m13 = Lerp(m->transform.m13, height, 0.1f);
      DrawModelWires(*m, ORIGIN, 1.0f, WHITE);
    }
  }
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
