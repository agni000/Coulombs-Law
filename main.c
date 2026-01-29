#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 30
#define MAX_CHARGES 20
#define CHARGE_RADIUS 20

typedef struct {
  float x; 
  float y; 
} Vector;

typedef struct {
  Vector position; 
  Vector velocity;
  Vector force; 
  float charge;
  Color color; 
} Charge; 

Charge CreateCharge(Vector pos, Vector vel, Vector frc, float chr, Color col);

int main() {
  InitWindow(WIDTH, HEIGHT, "Coulomb's Law");
  SetTargetFPS(FPS);

  Charge *charges = (Charge*)RL_CALLOC(MAX_CHARGES, sizeof(Charge)); 
  
  for (size_t i = 0; i < MAX_CHARGES; i++) {
    Vector pos = { GetRandomValue(CHARGE_RADIUS, WIDTH - CHARGE_RADIUS), GetRandomValue(CHARGE_RADIUS, HEIGHT - CHARGE_RADIUS) }; 
    Vector vel = { 0.0f, 0.0f };
    Vector frc = { 0.0f, 0.0f };
    float charge = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
    Color col = (charge > 0) ? RED : BLUE; 
    charges[i] = CreateCharge(pos, vel, frc, charge, col); 
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (size_t i = 0; i < MAX_CHARGES; i++) {
      DrawCircle(charges[i].position.x, charges[i].position.y, CHARGE_RADIUS, charges[i].color);
    }

    DrawFPS(10, 10);
    EndDrawing();
  }
  
  RL_FREE(charges);
  CloseWindow();

  return 0; 
}

Charge CreateCharge(Vector pos, Vector vel, Vector frc, float chr, Color col) {
  Charge c; 
  c.position = pos;
  c.velocity = vel;
  c.force = frc;
  c.charge = chr;
  c.color = col;
  return c; 
}

