#include "pellet.h"

Pellet::Pellet(int x, int y, float energy) {
    position.x = x;
    position.y = y;
    this->energy = energy;
    this->size = energy / 2;
}

void Pellet::Draw() {
    DrawCircle(position.x, position.y, size, DARKGREEN);
    DrawCircle(position.x, position.y, size * 0.7, LIME);
}