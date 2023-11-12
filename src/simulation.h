#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "weon.h"
#include "random"

class Simulation {
    public:
        Simulation();
        void Draw();
        void Update();
        void CreateWeones(int n);
        Camera2D camera;
        std::vector<Weon> weones;

    private:
        void HandleInput();
        void ClampCamera();
        float simulationWidth;
        float simulationHeight;
};