#ifndef PLANE_H
#define PLANE_H

#include "raylib.h"

#define ORIGIN (Vector3){0}
#define VECTOR_DOWN (Vector3){0.0f, -1.0f, 0.0f}
#define VECTOR_UP (Vector3){0.0f, 1.0f, 0.0f}

typedef struct {
  int row;
  int column;
} Offset;

typedef struct {
  int rowSize;
  int columnSize;
  Offset offset;
  Model *models;
} PlaneView;

typedef struct {
  int rowSize;
  int columnSize;
  float *heights;
} HeightMap;

typedef struct {
  RayCollision collision;
  Model tile;
} PlaneCollision;

extern PlaneView GeneratePlaneView(int rowSize, int columnSize,
                                   Texture texture);
extern void DrawPlaneView(PlaneView *plane, HeightMap map);
extern HeightMap GetHeightMap(int rowSize, int columnSize);
extern float GetHeightFromMap(HeightMap map, Offset offset, int row,
                              int column);
extern PlaneCollision GetPlaneCollision(PlaneView pv, Vector3 origin);

#endif
