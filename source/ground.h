#pragma once

#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class Ground
{
public:
    b2Body* body;
    int screenWidth;
    int screenHeight;
    

    Ground(b2World& world, int screenWidth, int screenHeight, Color col)
        : screenWidth(screenWidth), screenHeight(screenHeight)
    {
        b2BodyDef groundDef;
        groundDef.type = b2_staticBody;
        groundDef.position.Set((screenWidth / 2.0f) / SCALE, (screenHeight - 40.0f) / SCALE);
        body = world.CreateBody(&groundDef);

        b2PolygonShape groundShape;
        groundShape.SetAsBox((screenWidth / 2.0f) / SCALE, 20.0f / SCALE);
        body->CreateFixture(&groundShape, 0.0f);
    }

  void Draw()
    {
      float y = sinf(GetTime())+2.0f;
      for (int i = 1; i < 1000; i += 20) {
          DrawCircle(i, screenHeight-60, 20*y, Fade(GREEN,0.1f));// esto pa no perder el gusto de dibujar con primitivas de raylib
       }

        DrawRectangle(0, screenHeight - 60, screenWidth, 60, Fade(DARKPURPLE, 0.3f));
        DrawText(u8"  ¿ De cuantas formas podes derribar el tótem ? ", 30, 580, 18, WHITE);
        
    }
  
  
};