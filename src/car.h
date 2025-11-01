#ifndef CAR_H
#define CAR_H

#include "raylib.h"

typedef struct {
  Model body;
  Model wheels[4];
} Car;

Car GenerateCar(Model body);
void DrawCar(Car car);

#endif // !CAR_H
