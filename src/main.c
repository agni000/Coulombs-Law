#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 30
#define MAX_CHARGES 5
#define CHARGE_RADIUS 10
#define CONST_K 900000.0f
#define CHARGE_MASS 0.9f 
#define DAMPING 0.98f 

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
void CoulombsLaw(Charge *charges);
void UpdateCharges(Charge *charges, float dt); 

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
    CoulombsLaw(charges); 
    UpdateCharges(charges, 1.0f / FPS); 

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

/*@brief Apply the formula F = (K*(q1*q2)/(r^2))*û 
  @param The charges vector*/
void CoulombsLaw(Charge *charges) {
  /*reset forces for each calculation*/
  for (size_t i = 0; i < MAX_CHARGES; i++) {
    charges[i].force.x = 0.0f;
    charges[i].force.y = 0.0f;
  }

  for (size_t i = 0; i < MAX_CHARGES; i++) {
    for (size_t j = i + 1; j < MAX_CHARGES; j++) {
      float dx = charges[j].position.x - charges[i].position.x; 
      float dy = charges[j].position.y - charges[i].position.y; 
      
      float distance = (float)sqrt((double)(dx*dx + dy*dy)); 
      
      /*avoid division by zero*/
      if (distance < 5) distance = 9999;

      /*unit vectors*/ 
      float ux = dx / distance; 
      float uy = dy / distance; 
      
      float forceMagnitude = (CONST_K) * (charges[i].charge * charges[j].charge) / (distance * distance); 
      
      float fx = forceMagnitude * ux; 
      float fy = forceMagnitude * uy; 
     
      /*same intensity but opposite directions*/
      charges[i].force.x += fx;
      charges[i].force.y += fy;
      charges[j].force.x -= fx; 
      charges[j].force.y -= fy; 

      printf("fx: %.3f\nfy: %.3f\n", fx, fy);
    }
  }
}

/*@brief Since I have the Force calculated with CoulombsLaw(), I can find the acceleration, velocity and position of the charge to update the interactions
 @params The charges vector and delta-time*/
void UpdateCharges(Charge *charges, float dt) {
  for (size_t i = 0; i < MAX_CHARGES; i++) {
    /* (F = (m * a)) then (a = (F / m)) */
    float ax = charges[i].force.x / CHARGE_MASS; 
    float ay = charges[i].force.y / CHARGE_MASS; 
    
    /* (a = (dv / dt)) then (dv = (a * dt)) */
    charges[i].velocity.x += ax * dt; 
    charges[i].velocity.y += ay * dt;

    /* DAMPING test */
    charges[i].velocity.x *= DAMPING; 
    charges[i].velocity.y *= DAMPING; 

    /* (v = (ds / dt)) then (ds = (v * dt)) */ 
    charges[i].position.x += charges[i].velocity.x * dt; 
    charges[i].position.y += charges[i].velocity.y * dt;
   
    /* boundary conditions */
    if (charges[i].position.x < CHARGE_RADIUS || charges[i].position.x > WIDTH - CHARGE_RADIUS) {
        charges[i].velocity.x *= -0.8f;
        charges[i].position.x = (charges[i].position.x < CHARGE_RADIUS) ? CHARGE_RADIUS : WIDTH - CHARGE_RADIUS;
    }
    if (charges[i].position.y < CHARGE_RADIUS || charges[i].position.y > HEIGHT - CHARGE_RADIUS) {
        charges[i].velocity.y *= -0.8f;
        charges[i].position.y = (charges[i].position.y < CHARGE_RADIUS) ? CHARGE_RADIUS : HEIGHT - CHARGE_RADIUS;
    }
  }
}
