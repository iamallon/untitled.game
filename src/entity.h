#include "raylib.h"
#include "raymath.h"

typedef struct{
  Model model;
  Vector3 pos;
  BoundingBox bbox;
}ent_entity;

extern void ent_move(ent_entity *p, int key);
