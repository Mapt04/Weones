#include "simulation.h"

Simulation::Simulation() {
    camera = {{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, {0, 0}};
    camera.zoom = 1.0f;
    simulationWidth = 12000;
    simulationHeight = 8000;
    CreateWeones(100);
    CreatePellets(100);
}

void Simulation::Draw() {
    DrawCircleGradient(0, 0, simulationWidth/2, {0, 255, 0, 10}, {0, 20, 13, 30});
    DrawRectangleLinesEx({-simulationWidth/2, -simulationHeight/2, simulationWidth, simulationHeight}, 10, WHITE);
    for (int i = 0; i < pellets.size(); i++) {
        pellets[i].Draw();
    }
    for (int i = 0; i < weones.size(); i++) {
        weones[i].Draw();
    }
}

void Simulation::Update() {
    HandleInput();
    for (int i = 0; i < weones.size(); i++) {
        weones[i].Update();
    }
}

void Simulation::CreateWeones(int n) {
    std::uniform_real_distribution<double> unif(0, 2 * PI);
    std::default_random_engine re;

    for(int i = 0; i < n; i++) {
        Weon newWeon = Weon();
        newWeon.position.x = rand() % (int)simulationWidth - (int)simulationWidth/2;
        newWeon.position.y = rand() % (int)simulationHeight - (int)simulationHeight/2;
        newWeon.Rotate(unif(re));
        newWeon.simulationWidth = simulationWidth;
        newWeon.simulationHeight = simulationHeight;
        weones.push_back(newWeon);
    }
}

void Simulation::CreatePellets(int n) {
    for(int i = 0; i < n; i++) {
        int x = rand() % (int)simulationWidth - (int)simulationWidth/2;
        int y = rand() % (int)simulationHeight - (int)simulationHeight/2;
        float energy = rand() % 100 + 50;
        Pellet newPellet = Pellet(x, y, energy);
        pellets.push_back(newPellet);
    }
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

