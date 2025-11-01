#ifndef PHYSICS_H
#define PHYSICS_H

#include "car.h"
#include "plane.h"
#include "raylib.h"

void ApplyCarPhysics(PlaneView p, Car *car);
void ApplyCarInput(PlaneView p, Car *car);

#endif
