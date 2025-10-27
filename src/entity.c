#include "entity.h"

static float step = 10.0f;

void ent_move(ent_entity *p, int key) {
  if (key == 0) {
    return;
  }

  if (key == KEY_UP) {
    p->pos = Vector3Add(p->pos, (Vector3){step, 0, 0});
    p->bbox.min = Vector3Add(p->bbox.min, (Vector3){step, 0, 0});
    p->bbox.max = Vector3Add(p->bbox.max, (Vector3){step, 0, 0});
  }

  if (key == KEY_DOWN) {
    p->pos = Vector3Add(p->pos, (Vector3){-step, 0, 0});
    p->bbox.min = Vector3Add(p->bbox.min, (Vector3){-step, 0, 0});
    p->bbox.max = Vector3Add(p->bbox.max, (Vector3){-step, 0, 0});
  }

  if (key == KEY_LEFT) {
    p->pos = Vector3Add(p->pos, (Vector3){0, 0, step});
    p->bbox.min = Vector3Add(p->bbox.min, (Vector3){0, 0, step});
    p->bbox.max = Vector3Add(p->bbox.max, (Vector3){0, 0, step});
  }

  if (key == KEY_RIGHT) {
    p->pos = Vector3Add(p->pos, (Vector3){0, 0, -step});
    p->bbox.min = Vector3Add(p->bbox.min, (Vector3){0, 0, -step});
    p->bbox.max = Vector3Add(p->bbox.max, (Vector3){0, 0, -step});
  }
}
