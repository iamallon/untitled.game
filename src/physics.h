#ifndef PHYSICS_H
#define PHYSICS_H

#include "car.h"
#include "plane.h"
#include "raylib.h"

Vector3 GetPosition(Matrix m);
void ApplyCarPhysics(PlaneView p, Car *car);
void ApplyCarInput(PlaneView p, Car *car);

#endif
