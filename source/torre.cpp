#include "Torre.h"
#include "ResourceManager.h"

// tamanio de cada bloque
static constexpr float BLK_W = 28.0f;
static constexpr float BLK_H = 28.0f;


Torre::Torre(b2World& world, float baseX, float baseY)
{
    const int FILAS = 6;

    for (int fila = 0; fila < FILAS; fila++)
    {
        float cx = baseX + BLK_W;
        float cy = baseY - fila * (BLK_H * 2) - BLK_H;

        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set(cx / SCALE, cy / SCALE);
        b2Body* body = world.CreateBody(&def);

        b2PolygonShape shape;
        shape.SetAsBox(BLK_W / SCALE, BLK_H / SCALE);

        b2FixtureDef fix;
        fix.shape = &shape;
        fix.density = 2.0f;
        fix.friction = 0.5f;
        fix.restitution = 0.1f;
        body->CreateFixture(&fix);
           

        bloques.push_back({ body, BLK_W / SCALE, BLK_H / SCALE, fila });
    }
}


void Torre::Draw()
{
    Texture2D& tex = ResourceManager::GetTexture("torre");

    for (auto& blk : bloques)
    {
        b2Vec2 pos = blk.body->GetPosition();
        float  angle = blk.body->GetAngle();

        float cx = pos.x * SCALE;
        float cy = pos.y * SCALE;

        float w = blk.halfW * 2 * SCALE;
        float h = blk.halfH * 2 * SCALE;

       
        Rectangle source = { 0, (5 - blk.fila) * 64.0f, 64.0f, 64.0f };
        Rectangle dest = { cx, cy, w, h };
        Vector2   origin = { w / 2, h / 2 };

        DrawTexturePro(tex, source, dest, origin, angle * RAD2DEG, WHITE);
    }
}

void Torre::SetContactListener(b2World& world, b2Body* cargaBody)
{
    listener.torre = this; //apunto (puntero) a la instancia de torre
    
    world.SetContactListener(&listener);
}

void Torre::TorreContactListener::BeginContact(b2Contact* contact)
{
    b2Body* A = contact->GetFixtureA()->GetBody();
    b2Body* B = contact->GetFixtureB()->GetBody();

   for (auto& blk : torre->bloques)
    {
        if (A == blk.body || B == blk.body) //si uno de los dos bodies involucrados es un bloque de la torre, flagueo golpe
        {
            torre->golpe = true;
            return;
        }
    }
}