#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

extern const float SCALE;

class Torre
{
public:
    struct Bloque
    {
        b2Body* body;
        float   halfW;
        float   halfH;
        int     fila;
    };

    std::vector<Bloque> bloques;
    bool golpe = false;

    Torre(b2World& world, float baseX, float baseY);

    void SetContactListener(b2World& world, b2Body* cargaBody);
    void Draw();

private:
    class TorreContactListener : public b2ContactListener// esto es para detectar la colision y asignarle un sonido, o cualquier otra cosa
    {
    public:
        Torre* torre = nullptr;
        b2Body* cargaBody = nullptr;

        void BeginContact(b2Contact* contact) override;
    };

    TorreContactListener listener;
};