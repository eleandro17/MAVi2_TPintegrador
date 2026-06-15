#include "loopdeJuego.h"
#include "Carga.h"
#include "ResourceManager.h"

LoopDeJuego::LoopDeJuego(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{
    Music& music = ResourceManager::GetMusic("fondomusic");
    PlayMusicStream(music);
}
LoopDeJuego::~LoopDeJuego()
{
    StopMusicStream(ResourceManager::GetMusic("fondomusic"));
}

bool LoopDeJuego::Run(b2World& world, Ground& ground,
    Brazo& brazo, Carga& carga, Torre& torre, Contraperson& contraperson)
{
    while (!WindowShouldClose())
    {
        world.Step(1.0f / 60.0f, 8, 3);
        UpdateMusicStream(ResourceManager::GetMusic("fondomusic"));
        HandleInput(brazo, carga, world, contraperson);
        Draw(ground, brazo, carga, torre, contraperson);

        if (IsKeyPressed(KEY_R))
            return true;   // reiniciar

        //chequeo de la collision de la torre/totem        
        if (torre.golpe)
        {
            if (carga.suelta) // esta condicion es solo para evitar el sonido cuando torre colisiona contra el piso al iniciar. No es una lógica del todo sensata, pero por ahora va
                PlaySound(ResourceManager::GetSound("pas"));
            torre.golpe = false;
        }
    }
    return false;  // cierrad la ventana  
    
}

void LoopDeJuego::HandleInput(Brazo& brazo, Carga& carga, b2World& world, Contraperson& contraperson)
{
    brazo.HandleInput(world);
    contraperson.HandleInput();
}

void LoopDeJuego::Draw(Ground& ground, Brazo& brazo, Carga& carga, Torre& torre, Contraperson& contraperson)
{
    BeginDrawing();
    //DrawRectangle(0, 0, 1000, 600, { 30, 30, 46, 65 });
    Texture2D& tex = ResourceManager::GetTexture("fondo");
    DrawTexture(tex, 0, 0, { 200, 200, 200, 65 });

    ground.Draw();
    torre.Draw();
    brazo.Draw();
    carga.Draw(brazo.body);
    contraperson.Draw(brazo.body);

    // HUD
    DrawRectangleGradientV(0, 0, 830, 90, Fade(BLACK, 0.2f),BLANK);
    DrawText(u8"  ----  TP integrador: Demolición indirecta  ----", 30, 12, 28, YELLOW);
    DrawText(" A / D mover contraperson |  ESPACIO: impulso |", 20, 50, 18, WHITE);
    DrawText(" Flechas verticales: variar cable | Q : SOLTAR la bola ", 430, 50, 18, WHITE);
    DrawText("         (R)einiciar  ", 20, 86, 18,ORANGE);
   

    if (carga.suelta)
    {
        DrawRectangle(10, 126, 280, 28, Fade(RED, 0.3f));
        DrawText(" BOLA SUELTA !", 14, 131, 18, MAGENTA);
    }

    Rectangle rect = { screenWidth - 100.0f, 10.0f, 100, 80 };
    DrawRectangleGradientEx(rect, Fade(DARKPURPLE, 0.3f), BLANK, ORANGE, Fade(BLUE, 0.2f));
    DrawFPS(screenWidth - 80, 20);

    EndDrawing();
}