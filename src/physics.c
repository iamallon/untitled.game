#include "physics.h"
#include "car.h"
#include "plane.h"
#include "raylib.h"
#include "raymath.h"
#include <math.h>

#define GRAVITY 9.8f
#define SPRING_FORCE 1.4f
#define CAR_VELOCITY 3.0f
#define ROTATION_SPEED 5.0f

static Vector3 GetPosition(Matrix m) { return (Vector3){m.m12, m.m13, m.m14}; }

static BoundingBox GetRotationAwareModelBoundingBox(Model model) {
  Mesh mesh = model.meshes[0];
  float *vertices = mesh.vertices;
  int vertexCount = mesh.vertexCount;

  BoundingBox bb = {0};
  Vector3 v = {vertices[0], vertices[1], vertices[2]};

  v = Vector3Transform(v, model.transform);

  bb.min = v;
  bb.max = v;

  for (int i = 0; i < vertexCount * 3; i += 3) {
    float x = vertices[i];
    float y = vertices[i + 1];
    float z = vertices[i + 2];

    Vector3 vtx = {x, y, z};
    vtx = Vector3Transform(vtx, model.transform);

    if (vtx.x < bb.min.x)
      bb.min.x = vtx.x;
    if (vtx.y < bb.min.y)
      bb.min.y = vtx.y;
    if (vtx.z < bb.min.z)
      bb.min.z = vtx.z;

    if (vtx.x > bb.max.x)
      bb.max.x = vtx.x;
    if (vtx.y > bb.max.y)
      bb.max.y = vtx.y;
    if (vtx.z > bb.max.z)
      bb.max.z = vtx.z;
  }

  return bb;
}

static Matrix RotateInPlaceZ(Matrix m, float deg) {
  // Translate to origin (0,0,0).
  Vector3 oldTranslate = GetPosition(m);
  Matrix result = MatrixMultiply(
      m, MatrixTranslate(-oldTranslate.x, -oldTranslate.y, -oldTranslate.z));

  // Rotate in regards to origin.
  result = MatrixMultiply(result, MatrixRotateZ(DEG2RAD * deg));

  // Translate back to original point.
  result = MatrixMultiply(
      result, MatrixTranslate(oldTranslate.x, oldTranslate.y, oldTranslate.z));

  return result;
}

static Matrix GetWheelMatrixTranslate(PlaneView p, Model m) {
  PlaneCollision col = GetPlaneCollision(p, GetPosition(m.transform));
  float highTile = GetModelBoundingBox(col.tile).max.y;
  float lowModel = GetRotationAwareModelBoundingBox(m).min.y;
  DrawBoundingBox(GetRotationAwareModelBoundingBox(m), RED);

  // This means we rest on the tile.
  if (fabs(highTile - lowModel) < 0.05f) {
    return MatrixIdentity();
  }

  // If there is a gap make the object fall.
  if (col.collision.hit && highTile < lowModel) {
    return MatrixTranslate(0, -SPRING_FORCE * GetFrameTime() * 0.7f, 0);
  }

  // If there is a bump make the object rise slightly.
  if (col.collision.hit && highTile > lowModel) {
    return MatrixTranslate(0, SPRING_FORCE * GetFrameTime() * 0.7f, 0);
  }

  return MatrixIdentity();
}

void ApplyCarPhysics(PlaneView p, Car *c) {
  Matrix FL = GetWheelMatrixTranslate(p, c->wheels[0]);
  Matrix FR = GetWheelMatrixTranslate(p, c->wheels[1]);
  Matrix BL = GetWheelMatrixTranslate(p, c->wheels[2]);
  Matrix BR = GetWheelMatrixTranslate(p, c->wheels[3]);

  c->wheels[0].transform = MatrixMultiply(c->wheels[0].transform, FL);
  c->wheels[1].transform = MatrixMultiply(c->wheels[1].transform, FR);
  c->wheels[2].transform = MatrixMultiply(c->wheels[2].transform, BL);
  c->wheels[3].transform = MatrixMultiply(c->wheels[3].transform, BR);

  // This is maybe a bad idea. Maybe the body needs it's own collision
  // detection?
  if (FL.m13 < 0 && FR.m13 < 0 && BL.m13 < 0 && BR.m13 < 0) {
    c->body.transform =
        MatrixMultiply(c->body.transform, MatrixTranslate(0, BL.m13, 0));
  }
}

// Order is: scale -> rotation -> translation
void ApplyCarInput(PlaneView p, Car *c) {
  if (IsKeyDown(KEY_H)) {
    Matrix move = MatrixTranslate(-CAR_VELOCITY * GetFrameTime(), 0, 0);

    c->body.transform = MatrixMultiply(c->body.transform, move);
    c->wheels[0].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[0].transform, ROTATION_SPEED), move);
    c->wheels[1].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[1].transform, ROTATION_SPEED), move);
    c->wheels[2].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[2].transform, ROTATION_SPEED), move);
    c->wheels[3].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[3].transform, ROTATION_SPEED), move);
  }

  if (IsKeyDown(KEY_L)) {
    Matrix move = MatrixTranslate(CAR_VELOCITY * GetFrameTime(), 0, 0);

    c->body.transform = MatrixMultiply(c->body.transform, move);
    c->wheels[0].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[0].transform, ROTATION_SPEED), move);
    c->wheels[1].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[1].transform, ROTATION_SPEED), move);
    c->wheels[2].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[2].transform, ROTATION_SPEED), move);
    c->wheels[3].transform = MatrixMultiply(
        RotateInPlaceZ(c->wheels[3].transform, ROTATION_SPEED), move);
  }
}
