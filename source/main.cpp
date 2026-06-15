#ifndef NDEBUG
//#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include "ground.h"
#include "Brazo.h"
#include "Carga.h"
#include "Torre.h"
#include "Init.h"
#include "loopdeJuego.h"
#include "ResourceManager.h"

const float SCALE = 30.0f;

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    Init::InitVentana(screenWidth, screenHeight,
        "MAVII - TP INTEGRADOR. Gomez Viera Emilio Leandro", 60);
    Init::InitAudio();
    ResourceManager::Init();

    bool reiniciar = true;
    while (reiniciar)
    {
        b2Vec2  gravity(0.0f, 9.8f);
        b2World world(gravity);

        Ground ground(world, screenWidth, screenHeight, Fade(DARKGREEN, 0.7f));

        b2BodyDef pivoteDef;
        pivoteDef.type = b2_staticBody;
        pivoteDef.position.Set((screenWidth / 2.0f) / SCALE, (screenHeight / 2.0f) / SCALE);
        b2Body* pivote = world.CreateBody(&pivoteDef);

        Brazo brazo(world, pivote, 360, screenHeight / 2.0f, WHITE);

        Carga carga(world, brazo.body, 100.0f, screenHeight / 2.0f, WHITE);
        brazo.carga = &carga;

        Torre torre(world, 720.0f, screenHeight - 60.0f);

        torre.SetContactListener(world, carga.body);//acá llamo al escuchador decolision de la torre

        Contraperson contraperson(world, brazo.body, -100.0f,WHITE);

        LoopDeJuego loop(screenWidth, screenHeight);

        reiniciar = loop.Run(world, ground, brazo, carga, torre, contraperson);
    }

    ResourceManager::Unload();
    Init::CerrarAudio();
    Init::Cerrar();

    return 0;
}