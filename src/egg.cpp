#include "egg.h"

Egg::Egg(int x, int y, Weon parent) {
    position.x = x;
    position.y = y;
    this->parent = parent;
    creationTime = GetTime();
    readyToHatch = false;
}

void Egg::Draw() {
    DrawCircle(position.x, position.y, 50, LIGHTGRAY);
    DrawCircle(position.x, position.y, 30, GRAY);
}

void Egg::Update() {
    if(GetTime() - creationTime > 5) {
        readyToHatch = true;
    }
}