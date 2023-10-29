#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "weon.h"

class Simulation {
    public:
        Simulation();
        void Draw();
        void Update();
        Camera2D camera;
        Weon testWeon;

    private:
        void HandleInput();
        void ClampCamera();
        float simulationWidth;
        float simulationHeight;
};