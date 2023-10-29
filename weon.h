#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "neuralnetwork.h"

class Weon {
    public:
        Weon();
        void Draw();
        void Update();
        void Rotate(float angle);
        void RotateLeft();
        void RotateRight();
        void Forward();
        float rotation;
        Vector2 vel;
        std::vector<Vector2> points;
        Vector2 position;
        float simulationWidth;
        float simulationHeight;
        float health;
        float speed;
    private:
        float size;
        void CheckBounds();
        double creationTime;
};
