#include "Carga.h"
#include <algorithm> //otra vez algoritmo
#include "ResourceManager.h"

static constexpr float LARGO_CABLE = 40.0f;

static constexpr float CABLE_MIN = 10.0f;
static constexpr float CABLE_MAX = 100.0f;
//static constexpr float CABLE_STEP = 2.0f;

static constexpr float LARGO_CABLE_CP = 260.0f; // largo del cable lo dejo fijo

static constexpr float FUERZA_CP = 80.0f;


Carga::Carga(b2World& world, b2Body* brazoBody, float offsetX, float centerY, Color col)
    : radius(25.0f), color(col), suelta(false), joint(nullptr)
{
    b2Vec2 extremo = brazoBody->GetWorldPoint(b2Vec2(offsetX / SCALE, 0.0f));

    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(extremo.x, extremo.y + LARGO_CABLE / SCALE);
    body = world.CreateBody(&def);

    b2CircleShape shape;
    shape.m_radius = radius / SCALE;

    b2FixtureDef fix;
    fix.shape = &shape;
    fix.density = radius/6;   // 
    fix.friction = 0.2f;
    fix.restitution = 0.5f;
    body->CreateFixture(&fix);

    b2DistanceJointDef jointDef;
    jointDef.Initialize(brazoBody, body, extremo, body->GetPosition());
    jointDef.minLength = LARGO_CABLE / SCALE;
    jointDef.maxLength = LARGO_CABLE / SCALE;
    jointDef.collideConnected = true;

    joint = (b2DistanceJoint*)world.CreateJoint(&jointDef);
}

void Carga::Soltar(b2World& world)
{
    if (!suelta && joint)
    {
        world.DestroyJoint(joint);
        joint = nullptr;
        suelta = true;

        // Empujón extra en la dirección de la velocidad actual
        b2Vec2 vel = body->GetLinearVelocity();
        body->ApplyLinearImpulseToCenter(b2Vec2(vel.x * 0.4f, vel.y * 0.4f), true);
    }
}


void Carga::Draw(b2Body* brazoBody)
{
    b2Vec2 pos = body->GetPosition();
    float cx = pos.x * SCALE;
    float cy = pos.y * SCALE;

    // cable
    if (!suelta)
    {
        b2Vec2 extremo = brazoBody->GetWorldPoint(b2Vec2(100.0f / SCALE, 0.0f));
        float ex = extremo.x * SCALE;
        float ey = extremo.y * SCALE;
        DrawLineEx({ ex, ey }, { cx, cy }, 4.0f, DARKGRAY);
    }

    Texture2D& tex = ResourceManager::GetTexture("carga");

    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { cx, cy, radius * 2, radius * 2 };
    Vector2   origin = { radius, radius };

    DrawTexturePro(tex, source, dest, origin, 0.0f, color);

    if (suelta) {
        DrawCircle((int)cx, (int)cy, radius -5.0f, Fade(RED, 0.5f));
        //DrawTexturePro(tex, source, dest, origin, 0.0f, YELLOW);
    }
        
}

void Carga::AjustarCable(float delta)
{
    if (suelta || !joint) return;

    float actual = joint->GetMaxLength() * SCALE;
    float nueva = std::clamp(actual + delta, CABLE_MIN, CABLE_MAX);

    joint->SetMinLength(nueva / SCALE);
    joint->SetMaxLength(nueva / SCALE);
}



Contraperson::Contraperson(b2World& world, b2Body* brazoBody, float offsetX, Color col )
    : radius(50.0f), color(col)
{
    b2Vec2 extremo = brazoBody->GetWorldPoint(b2Vec2(offsetX / SCALE, 0.0f));


    float groundY = (600.0f - 60.0f - radius) / SCALE; // screenHeight - grosor ground - radio

    
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(extremo.x, groundY);
    body = world.CreateBody(&def);

    b2CircleShape shape;
    shape.m_radius = radius / SCALE;

    b2FixtureDef fix;
    fix.shape = &shape;
    fix.density = radius/10.0f;//
    fix.friction = 0.2f;
    fix.restitution = 0.5f;
    body->CreateFixture(&fix);
        
    b2DistanceJointDef jointDef;
    jointDef.Initialize(brazoBody, body, extremo, body->GetPosition());
    jointDef.minLength = LARGO_CABLE_CP *0.2/ SCALE;
    jointDef.maxLength = LARGO_CABLE_CP/ SCALE;
    //b2LinearStiffness(jointDef.stiffness, jointDef.damping, 1.0f, 0.5f, brazoBody, body);
    jointDef.stiffness = 0.0f;
    jointDef.damping = 0.0f;
    
    jointDef.collideConnected = true;

    joint = (b2DistanceJoint*)world.CreateJoint(&jointDef);// 
}

void Contraperson::Draw(b2Body* brazoBody)
{
    b2Vec2 pos = body->GetPosition();
    float cx = pos.x * SCALE;
    float cy = pos.y * SCALE;

    // SOGA
    b2Vec2 extremo = brazoBody->GetWorldPoint(b2Vec2(-100.0f / SCALE, 0.0f));
    float ex = extremo.x * SCALE;
    float ey = extremo.y * SCALE;
    DrawLineEx({ ex, ey }, { cx, cy }, 2.0f, RAYWHITE);

    Texture2D& tex = ResourceManager::GetTexture("contraperson");

    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { cx, cy, radius * 2, radius * 2 };
    Vector2   origin = { radius, radius };

    DrawTexturePro(tex, source, dest, origin, 0.0f, color);

    //DrawCircleLines((int)cx, (int)cy, radius, DARKGRAY); // era solo para debuggear pero queda
}

void Contraperson::HandleInput()
{
    if (IsKeyDown(KEY_D))
    {
        direction = 1;
        body->ApplyForceToCenter(b2Vec2(FUERZA_CP, 0.0f), true);
    }
    if (IsKeyDown(KEY_A))
    {
        direction = -1;
        body->ApplyForceToCenter(b2Vec2(-FUERZA_CP, 0.0f), true);
    }

    // acumular
    if (IsKeyDown(KEY_SPACE))
    {
        fuerzaActual += 3.0f;
        fuerzaActual = fminf(fuerzaActual, IMPULSO_MAXIMO);

        unsigned char g = (unsigned char)(255 * (1.0f - fuerzaActual / IMPULSO_MAXIMO));
        color = { 255, g, g, 255 };
    }
    //  soltar
    if (IsKeyReleased(KEY_SPACE))
    {
        body->ApplyLinearImpulseToCenter(b2Vec2(direction * fuerzaActual, 0.0f), true);
        fuerzaActual = 0.0f;
        color = WHITE; // vuelve 
        PlaySound(ResourceManager::GetSound("impulso"));
    }
}