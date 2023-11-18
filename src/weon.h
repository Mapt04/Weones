#pragma once
#include "raylib.h"
#include "raymath.h"
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
        void Resize(float newSize);
        float rotation;
        Vector2 vel;
        std::vector<Vector2> points;
        Vector2 position;
        float simulationWidth;
        float simulationHeight;
        float health;
        float speed;
        NeuralNetwork brain;
        float size;
        float energy;

    private:
        void CheckBounds();
        double creationTime;
};
