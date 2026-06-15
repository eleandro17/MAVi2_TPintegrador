#include "Init.h"

namespace Init
{
    void InitVentana(int screenWidth, int screenHeight, const char* title, int fps)
    {
        InitWindow(screenWidth, screenHeight, title);
        SetTargetFPS(fps);
    }

    void InitAudio()
    {
        InitAudioDevice();
    }

    void CerrarAudio()
    {
        CloseAudioDevice();
    }

    void Cerrar()
    {
        CloseWindow();
    }
}