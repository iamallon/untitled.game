#include "camera.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

int main(void) {
  InitWindow(1280, 720, "untitled.game");
  SetTargetFPS(60);
  Model model = LoadModelFromMesh(GenMeshCube(10, 10, 10));
  BoundingBox bbox = GetModelBoundingBox(model);
  bbox.min = Vector3Scale(bbox.min, 2.0f);
  bbox.max = Vector3Scale(bbox.max, 2.0f);

  plr_player player = {model, (Vector3){5, 5, 5}, bbox};

  while (!WindowShouldClose()) {
    cam_begin();

    plr_move(&player, GetKeyPressed());
    DrawModel(player.model, player.pos, 1.0f, WHITE);
    DrawBoundingBox(player.bbox, RED);
    DrawGrid(40, 10);
    cam_end();
  }

  CloseWindow();

  return 0;
}
