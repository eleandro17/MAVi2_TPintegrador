#include "Brazo.h"
//#include <algorithm>
#include "ResourceManager.h"


static constexpr float TORQUE = 80.0f;
static constexpr float IMPULSO = 100.0f;
//static constexpr float LIMIT = b2_pi; // 180°

Brazo::Brazo(b2World& world, b2Body* pivoteBody, float centerX, float centerY, Color col)
    : halfW(100.0f), halfH(10.0f), color(col), direction(1)
{
    // Body dinámico centrado en el pivote
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(centerX / SCALE, centerY / SCALE);
    body = world.CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(halfW / SCALE, halfH / SCALE);

    b2FixtureDef fix;
    fix.shape = &shape;
    fix.density = 1.0f;
    fix.friction = 0.3f;
    body->CreateFixture(&fix);

    // Revolute Joint 

    b2RevoluteJointDef jointDef;
    jointDef.Initialize(pivoteBody, body, body->GetPosition()); // pivot en el centro
    jointDef.enableLimit = false;
    jointDef.enableMotor = false;
    jointDef.collideConnected = false;
    joint = (b2RevoluteJoint*)world.CreateJoint(&jointDef);

   }

void Brazo::HandleInput(b2World& world)
{
   
    if (carga)
    {
        if (IsKeyDown(KEY_UP))   carga->AjustarCable(-2.0f);
        if (IsKeyDown(KEY_DOWN)) carga->AjustarCable(+2.0f);
    }
    
    //soltar bola
    if (IsKeyPressed(KEY_Q))
    {
        carga->Soltar(world);
        PlaySound(ResourceManager::GetSound("soltar")); // 
    }

}


    void Brazo::Draw()
    {
        b2Vec2 pos = body->GetPosition();
        float  angle = body->GetAngle();

        float cx = pos.x * SCALE;
        float cy = pos.y * SCALE;

        Texture2D& tex = ResourceManager::GetTexture("brazo");

        // todo el PNG 
        Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };

       
        Rectangle dest = { cx, cy, halfW * 2, halfH * 2 };

        // origen en el centro para que rote bien
        Vector2 origin = { halfW, halfH };

        DrawTexturePro(tex, source, dest, origin, angle * RAD2DEG, color);

        // punto de punta, lo dejo para debug por ahora
        b2Vec2 punta = body->GetWorldPoint(b2Vec2(halfW / SCALE, 0.0f));
        DrawCircle((int)(punta.x * SCALE), (int)(punta.y * SCALE), 6.0f, RED);
    }


