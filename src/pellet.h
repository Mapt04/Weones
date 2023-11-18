#pragma once
#include "raylib.h"

class Pellet
{
  public:
    Vector2 position;
    float energy;
    float size;

    Pellet(int x, int y, float energy);
    void Draw();
    bool ContainsPoint(Vector2 point);
};