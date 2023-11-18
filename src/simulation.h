#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "weon.h"
#include "random"
#include "pellet.h"
#include "egg.h"

class Simulation {
    public:
        Simulation();
        void Draw();
        void DrawWeones();
        void DrawPellets();
        void DrawEggs();
        void Update();
        void UpdateWeones();
        void CreateWeones(int n);
        void CreatePellets(int n);
        void CreateEgg(Weon parent);
        void HatchEgg(Egg egg);
        void UpdateEggs();
        Camera2D camera;
        std::vector<Weon> weones;
        std::vector<Pellet> pellets;
        std::vector<Egg> eggs;

    private:
        void HandleInput();
        void ClampCamera();
        void CheckCollisions();
        float simulationWidth;
        float simulationHeight;
};