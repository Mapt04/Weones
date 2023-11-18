#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "weon.h"
#include "random"
#include "pellet.h"

class Simulation {
    public:
        Simulation();
        void Draw();
        void DrawWeones();
        void DrawPellets();
        void Update();
        void CreateWeones(int n);
        void CreatePellets(int n);
        Camera2D camera;
        std::vector<Weon> weones;
        std::vector<Pellet> pellets;

    private:
        void HandleInput();
        void ClampCamera();
        void CheckCollisions();
        float simulationWidth;
        float simulationHeight;
};