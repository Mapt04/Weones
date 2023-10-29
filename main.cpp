#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "simulation.h"

int main() {

    InitWindow(1200, 800, "Weones");
    SetTargetFPS(60);

    Simulation simulation = Simulation();

    while (!WindowShouldClose()) {

        //Update
        if(IsKeyDown(KEY_Q)) {
            simulation.testWeon.RotateLeft();
        }
        if(IsKeyDown(KEY_E)) {
            simulation.testWeon.RotateRight();
        }

        if(IsKeyDown(KEY_W)) {
            simulation.testWeon.Forward();
        }
        simulation.Update();
        
        //Draw

        BeginDrawing();
        ClearBackground({0, 20, 13, 255});
        BeginMode2D(simulation.camera);



        simulation.Draw();


        EndMode2D();
        
        DrawText(TextFormat("CURRENT FPS: %i", int(round((1.0f/GetFrameTime())))), GetScreenWidth() - 220, 40, 20, GREEN);
        DrawText(TextFormat("ROTATION: %i", int(round((simulation.testWeon.rotation)))), GetScreenWidth() - 220, 100, 20, GREEN);

        EndDrawing();

        

    }

    CloseWindow();
    return 0;
}