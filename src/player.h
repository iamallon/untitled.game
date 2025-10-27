#include "raylib.h"
#include "raymath.h"

typedef struct{
  Model model;
  Vector3 pos;
  BoundingBox bbox;
}plr_player; 

extern void plr_move(plr_player *p, int key);
