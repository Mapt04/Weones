#include "weon.h"
#include <iostream>

Weon::Weon() : brain(2, 5, 4){
    position = (Vector2){0, 0};
    size = 10.0f;
    rotation = 0.0f;
    points = {(Vector2){0.0f, -10.0f}, (Vector2){-5.0f, 5.0f}, (Vector2){5.0f, 5.0f}};
    for (int i = 0; i < points.size(); i++) {
        points[i] = Vector2Scale(points[i], size);
    }
    speed = 5.0f;
    vel.x = 0;
    vel.y = 0;
    energy = 100;
    brain.CreateNewConnection();
}

void Weon::Draw() {

    DrawTriangle(
        (Vector2)Vector2Add(points[0], position), 
        (Vector2)Vector2Add(points[1], position), 
        (Vector2)Vector2Add(points[2], position), 
        RAYWHITE);
    
}

void Weon::DrawShadow() {
    DrawTriangle(
        (Vector2)Vector2Add(Vector2Add(points[0], position), (Vector2){30, 30}), 
        (Vector2)Vector2Add(Vector2Add(points[1], position), (Vector2){30, 30}), 
        (Vector2)Vector2Add(Vector2Add(points[2], position), (Vector2){30, 30}), 
        Color{0, 0, 0, 100});
}

void Weon::Update() {
    position = Vector2Add(position, vel);
    vel = Vector2Add(vel, Vector2Scale(vel, -0.1));

    // energy -= 0.1;

    if(energy > 300) {
        readyToLayEgg = true;
    }
    else {
        readyToLayEgg = false;
    }

    if(energy <= 0) {
        // Die();
    }
}

void Weon::Rotate(float angle) {
    rotation = rotation + angle - (2 * PI) * int((rotation + angle) / (2 * PI));
    for(int i = 0; i < points.size(); i++) {
        points[i] = Vector2Rotate(points[i], angle);
    }
}

void Weon::RotateLeft() {
    Rotate(-0.05);
}

void Weon::RotateRight() {
    Rotate(0.05);
}

void Weon::Forward() {
    vel = Vector2Add(Vector2Rotate((Vector2){0, -speed}, rotation), vel);
}

void Weon::BounceH() {
    if(vel.x < 0 && position.x < 0 || vel.x > 0 && position.x > 0) {
        vel.x *= -1;
        Rotate(-2 * rotation);
    }
}

void Weon::BounceV() {
    if(vel.y < 0 && position.y < 0 || vel.y > 0 && position.y > 0) {
        vel.y *= -1;
        Rotate(-2 * rotation + PI);
    }
}

void Weon::Resize(float newSize) {
    for (int i = 0; i < points.size(); i++) {
        points[i] = Vector2Scale(points[i], size);
    }
}

void Weon::LayEgg() {
    energy -= 100;
    readyToLayEgg = false;
}