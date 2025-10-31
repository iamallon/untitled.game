#ifndef PLANE_H
#define PLANE_H

#include "raylib.h"

#define ORIGIN (Vector3){0}

typedef struct {
  int rowSize;
  int columnSize;
  Model *models;
} PlaneView;

typedef struct {
  int rowSize;
  int columnSize;
  float *heights;
} HeightMap;

extern PlaneView GeneratePlaneView(int rowSize, int columnSize);
extern void DrawPlaneView(PlaneView plane, HeightMap map, int offsetX, int offsetY);
extern HeightMap GetHeightMap(int rowSize, int columnSize);

#endif
