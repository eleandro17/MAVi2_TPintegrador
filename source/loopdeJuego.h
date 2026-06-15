#pragma once

#include "raylib.h"
#include <box2d.h>
#include "ground.h"
#include "Brazo.h"
#include "Carga.h"
#include "Torre.h"

class LoopDeJuego
{
public:
    LoopDeJuego(int screenWidth, int screenHeight);
    ~LoopDeJuego();

    bool Run(b2World& world, Ground& ground, Brazo& brazo,
        Carga& carga, Torre& torre, Contraperson& contraperson);
   
private:
    int screenWidth;
    int screenHeight;

    void HandleInput(Brazo& brazo, Carga& carga, b2World& world, Contraperson& contraperson);
    void Draw(Ground& ground, Brazo& brazo, Carga& carga, Torre& torre, Contraperson& contraperson);
   

};
