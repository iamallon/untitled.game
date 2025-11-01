#include "car.h"
#include "plane.h"
#include "raylib.h"
#include "raymath.h"

Car GenerateCar(Model body) {
  Car car = {0};

  car.body = body;
  car.body.transform = MatrixTranslate(9, 11, 11);
  car.wheels[0] = LoadModelFromMesh(GenMeshTorus(1.0f, 0.4f, 16, 32));
  car.wheels[0].transform = MatrixTranslate(10, 10, 10);
  car.wheels[1] = LoadModelFromMesh(GenMeshTorus(1.0f, 0.4f, 16, 32));
  car.wheels[1].transform = MatrixTranslate(10, 10, 12);
  car.wheels[2] = LoadModelFromMesh(GenMeshTorus(1.0f, 0.4f, 16, 32));
  car.wheels[2].transform = MatrixTranslate(8, 10, 10);
  car.wheels[3] = LoadModelFromMesh(GenMeshTorus(1.0f, 0.4f, 16, 32));
  car.wheels[3].transform = MatrixTranslate(8, 10, 12);

  return car;
}

void DrawCar(Car car) {
  DrawModelWires(car.body, ORIGIN, 1.0f, WHITE);
  DrawModelWires(car.wheels[0], ORIGIN, 1.0f, WHITE);
  DrawModelWires(car.wheels[1], ORIGIN, 1.0f, WHITE);
  DrawModelWires(car.wheels[2], ORIGIN, 1.0f, WHITE);
  DrawModelWires(car.wheels[3], ORIGIN, 1.0f, WHITE);
}
