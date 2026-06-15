#pragma once

#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class Carga
{
public:
    b2Body* body;
    b2DistanceJoint* joint;

    float radius;
    Color color;

    bool suelta = false;  // true una vez que se soltó el cable

    Carga(b2World& world, b2Body* brazoBody, float offsetX, float centerY, Color col);

    void Soltar(b2World& world);           // destruye el joint y libera la bola
    void Draw(b2Body* brazoBody);

    void AjustarCable(float delta); // positivo = alargar, negativo = acortar
};

class Contraperson
{
public:
    b2Body* body;
    b2DistanceJoint* joint;

    float radius;
    Color color;

    int direction = 1;

    float fuerzaActual = 0.0f;
    static constexpr float IMPULSO_MAXIMO = 300.0f;

    Contraperson(b2World& world, b2Body* brazoBody, float offsetX, Color col);

    void Draw(b2Body* brazoBody);

    void HandleInput();
};