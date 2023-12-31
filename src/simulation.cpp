#include "simulation.h"

Simulation::Simulation(){
    camera = {{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, {0, 0}};
    camera.zoom = 1.0f;
    simulationWidth = 15000;
    simulationHeight =  10000;
    CreateWeones(1);
    CreatePellets(70);
}

void Simulation::Draw() {
    DrawCircleGradient(0, 0, simulationWidth/2, {0, 255, 0, 10}, {0, 20, 13, 30});
    DrawRectangleLinesEx({-simulationWidth/2, -simulationHeight/2, simulationWidth, simulationHeight}, 10, WHITE);
    DrawPellets();
    DrawEggs();
    DrawWeones();
}

void Simulation::DrawWeones() {
    for (int i = 0; i < weones.size(); i++) {
        weones[i].DrawShadow();
    }

    for (int i = 0; i < weones.size(); i++) {
        weones[i].Draw();
    }
}

void Simulation::DrawPellets() {
    for (int i = 0; i < pellets.size(); i++) {
        pellets[i].Draw();
    }
}

void Simulation::DrawEggs() {
    for (int i = 0; i < eggs.size(); i++) {
        eggs[i].Draw();
    }
}

void Simulation::Update() {
    HandleInput();
    UpdateWeones();
    UpdateEggs();
    CheckCollisions();
}

void Simulation::UpdateWeones() {
    for (int i = 0; i < weones.size(); i++) {
        weones[i].Update();
        if(weones[i].readyToLayEgg) {
            CreateEgg(weones[i]);
            weones[i].LayEgg();
        }
    }
}

void Simulation::UpdateEggs() {
    for (int i = 0; i < eggs.size(); i++) {
        eggs[i].Update();
        if(eggs[i].readyToHatch) {
            HatchEgg(eggs[i]);
            eggs.erase(eggs.begin() + i);
        }
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

void Simulation::CreateEgg(Weon parent) {
    Egg newEgg = Egg(parent.position.x, parent.position.y, parent);
    eggs.push_back(newEgg);
}

void Simulation::HatchEgg(Egg egg) {
    Weon newWeon = Weon();
    newWeon.position = egg.position;
    newWeon.energy = 100;
    newWeon.size = egg.parent.size;
    newWeon.vel.x = 0;
    newWeon.vel.y = 0;
    newWeon.rotation = 0;
    weones.push_back(newWeon);

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
            else if (camera.zoom < 0.08f) camera.zoom = 0.08f;
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

void Simulation::CheckCollisions() {

    // Weon-Pellet Collisions

    for (int i = 0; i < weones.size(); i++) {
        for (int j = 0; j < pellets.size(); j++) {
            bool colliding = false;
            for(Vector2 vertex: weones[i].points) {
                if (pellets[j].ContainsPoint(Vector2Add(vertex, weones[i].position))) {
                    colliding = true;
                    break;
                }
            }

            if (colliding) {
                weones[i].energy += pellets[j].energy;
                pellets.erase(pellets.begin() + j);
            }
        }
    }

    // Weon-Border Collisions
    for (int i = 0; i < weones.size(); i++) {
        for(Vector2 vertex: weones[i].points) {
            if (vertex.x + weones[i].position.x < -simulationWidth/2 || vertex.x + weones[i].position.x > simulationWidth/2) {
                weones[i].BounceH();
                break;
            }

            if(vertex.y + weones[i].position.y < -simulationHeight/2 || vertex.y + weones[i].position.y > simulationHeight/2) {
                weones[i].BounceV();
            }
        }
    }
}
