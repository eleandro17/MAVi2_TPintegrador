
#pragma once
#include "raylib.h"

namespace Init
{
    void InitVentana(int screenWidth, int screenHeight, const char* title, int fps);
    void InitAudio();
    void CerrarAudio();
    void Cerrar();
}