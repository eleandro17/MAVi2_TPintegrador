#pragma once

#include "raylib.h"
#include <box2d.h>

#include "carga.h"

extern const float SCALE;

class Brazo
{
public:
    b2Body* body;
    b2RevoluteJoint* joint;//

    float halfW;   // mitad del largo en pixels
    float halfH;   // mitad del alto en pixels
    Color color;

    int direction; // +1 derecha(sentido horario seria), -1 izquierda 

    //float anchorOffset; // entre -halfW y +halfW
   // b2Body* pivoteBody; // guardo referencia para recrear el joint

   // float anchorFijo; // se actualiza solo se aprieta F

    Brazo(b2World& world, b2Body* pivoteBody, float centerX, float centerY, Color col);

    void HandleInput(b2World& world);
    void Draw();

   // void RecrearJoint(b2World& world);//

    Carga* carga = nullptr; // se asigna desde afuera
};
