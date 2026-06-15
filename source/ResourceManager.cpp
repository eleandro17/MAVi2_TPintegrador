#include "ResourceManager.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound>     ResourceManager::sounds;
std::unordered_map<std::string, Music>     ResourceManager::music;

void ResourceManager::Init()
{
    
    // Texturas
    LoadTexture("contraperson", "assets/contraperson.png");
    LoadTexture("fondo", "assets/fondo.png");
    LoadTexture("brazo", "assets/brazo.png");
    LoadTexture("carga", "assets/carga.png");
    LoadTexture("piso", "assets/vagon.png");
    LoadTexture("torre", "assets/torre2.png");

    // Sonidos
    LoadSound("soltar", "assets/bola.wav");
    LoadSound("impulso", "assets/impulso.wav");
    LoadSound("pas", "assets/pas.wav");

    // Música
    LoadMusic("fondomusic", "assets/TP_integrador_escena.wav");
}

void ResourceManager::Unload()
{
    for (auto& t : textures)
        UnloadTexture(t.second);

    for (auto& s : sounds)
        UnloadSound(s.second);

    for (auto& m : music)
        UnloadMusicStream(m.second);

}

void ResourceManager::LoadTexture(const std::string& id, const std::string& path)
{
    if (textures.count(id) == 0)
        textures[id] = ::LoadTexture(path.c_str());
}

Texture2D& ResourceManager::GetTexture(const std::string& id)
{
    auto it = textures.find(id);
    if (it == textures.end())
    {
        std::cerr << "ERROR: Texture not loaded: " << id << std::endl;
        static Texture2D dummy = { 0 };
        return dummy;
    }
    return it->second;
}

void ResourceManager::LoadSound(const std::string& id, const std::string& path)
{
    if (sounds.count(id) == 0)
        sounds[id] = ::LoadSound(path.c_str());
}

Sound& ResourceManager::GetSound(const std::string& id)
{
    auto it = sounds.find(id);
    if (it == sounds.end())
    {
        std::cerr << "ERROR: Sound not loaded: " << id << std::endl;
        static Sound dummy = { 0 };
        return dummy;
    }
    return it->second;
}

void ResourceManager::LoadMusic(const std::string& id, const std::string& path)
{
    if (music.count(id) == 0)
    {
        Music m = ::LoadMusicStream(path.c_str());
        if (m.stream.buffer == nullptr)
            std::cerr << "ERROR: no se pudo cargar música: " << path << std::endl;
        else
            music[id] = m;
    }
}

Music& ResourceManager::GetMusic(const std::string& id)
{
    auto it = music.find(id);
    if (it == music.end())
    {
        std::cerr << "ERROR: Music not loaded: " << id << std::endl;
        static Music dummy = { 0 };
        return dummy;
    }
    return it->second;
}