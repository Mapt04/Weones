#include "simulation.h"

Simulation::Simulation() {
    camera = {{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, {0, 0}};
    camera.zoom = 1.0f;
    simulationWidth = 12000;
    simulationHeight = 8000;
    testWeon = Weon();
    testWeon.simulationWidth = simulationWidth;
    testWeon.simulationHeight = simulationHeight;
}

void Simulation::Draw() {
    DrawCircleGradient(0, 0, simulationWidth/2, {0, 255, 0, 10}, {0, 20, 13, 30});
    DrawRectangleLinesEx({-simulationWidth/2, -simulationHeight/2, simulationWidth, simulationHeight}, 10, WHITE);
    testWeon.Draw();
}

void Simulation::Update() {
    HandleInput();
    // testWeon.Forward();
    // testWeon.Rotate(0.01);
    testWeon.Update();
    
}

void Simulation::HandleInput() {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }

        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            camera.zoom += ((float)GetMouseWheelMove()*0.05f);
            if (camera.zoom > 2.0f) camera.zoom = 2.0f;
            else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        }

        if (IsKeyPressed(KEY_R)) {
            camera.zoom = 1.0f;
            camera.offset = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
            camera.target = {0, 0};
        }
        ClampCamera();
}

void Simulation::ClampCamera() {
    if(camera.target.x + (GetScreenWidth()/2)/camera.zoom > simulationWidth/2) {
        camera.target.x = simulationWidth/2 - (GetScreenWidth()/2)/camera.zoom;
    }
    if(camera.target.x - (GetScreenWidth()/2)/camera.zoom < -simulationWidth/2) {
        camera.target.x = -simulationWidth/2 + (GetScreenWidth()/2)/camera.zoom;
    }
    if(camera.target.y + (GetScreenHeight()/2)/camera.zoom > simulationHeight/2) {
        camera.target.y = simulationHeight/2 - (GetScreenHeight()/2)/camera.zoom;
    }
    if(camera.target.y - (GetScreenHeight()/2)/camera.zoom < -simulationHeight/2) {
        camera.target.y = -simulationHeight/2 + (GetScreenHeight()/2)/camera.zoom;
    }
}

