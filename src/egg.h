#pragma once
#include "raylib.h"
#include "weon.h"

class Egg {
  public:
    Vector2 position;
    double creationTime;
    Weon parent;
    bool readyToHatch;

    Egg(int x, int y, Weon parent);
    void Draw();
    void Update();
};