#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:

    // inicialización
    static void Init();
    static void Unload();

    // TEXTURAS
    static void LoadTexture(const std::string& id, const std::string& path);
    static Texture2D& GetTexture(const std::string& id);

    // SONIDOS
    static void LoadSound(const std::string& id, const std::string& path);
    static Sound& GetSound(const std::string& id);

    // MUSICA
    static void LoadMusic(const std::string& id, const std::string& path);
    static Music& GetMusic(const std::string& id);

private:

    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<std::string, Sound> sounds;
    static std::unordered_map<std::string, Music> music;
};