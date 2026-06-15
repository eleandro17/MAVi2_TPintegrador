[README.md](https://github.com/user-attachments/files/28937776/README.md)
# MAVI II - TP integrador

**Gomez Viera Emilio Leandro**

## Demolicion Indirecta
Una especie de bola de demolición con tracción a sangre. Hay varias formas de manipular el brazo y la bola y liberar al tótem del  yugo de su verticalidad.
Me tomé bastante literal lo de  integrador y utilicé conceptos y códigos de los TPs anteriores, y algunas cosas de MAVI1. Un cuerpo que acumula impulso para moverse, pero que depende de otros cuerpos para liberarse. Y además de su propio impulso se ve influenciada por una 2 cuerdas que sujetan y oscilan. Son realmente 2 cargas pero cada una recibe inputs distintos y esto le da complejidad a la predicción del comportamiento de la bola.

## Controles
A y D mueven a contraperson ( el personaje: un chistemalo entre persona y contrapeso)
SPACEBAR  acumula fuerza para dar el impulso al SOLTAR.
Las flechitas verticales varían el largo del cable que sostiene la bola.
Q suelta la bola: solo hay una oportunidad
R reinicia la escena

 
##Bodies:

pivote — estático, punto de rotación del brazo
brazo.body — dinámico
carga.body — dinámico
contraperson.body — dinámico
ground.body — estático
bloques[vector] — 6 dinámicos (uno por fila de la torre/tótem)

Total: 10 bodies (4 únicos + 6 de la torre)

##Joints:

brazo.joint — b2RevoluteJoint entre pivote y brazo
carga.joint — b2DistanceJoint entre brazo y bola
contraperson.joint — b2DistanceJoint entre brazo y contraperson

Total: 3 joints



## ESTRUCTURA

main.cpp
├── Init::InitVentana()          
├── Init::InitAudio()            → inicializa dispositivo de audio
├── ResourceManager::Init()      → carga texturas, sonidos y música
├── while(reiniciar)             → loop de reinicio (tecla R)
│   ├── b2World                  → gravedad (0, 9.8)
│   ├── b2Body* pivote           → estático, centro de pantalla (500, 300)
│   ├── Ground                   → estático, piso
│   ├── Brazo                    → dinámico
│   ├── Carga                    → dinámico, colgada del extremo del brazo
│   ├── Torre                    → 6 bloques dinámicos
│   ├── Contraperson             → dinámico, extremo opuesto del brazo
│   └── LoopDeJuego::Run()       → devuelve bool (true=reiniciar, false=salir)
├── ResourceManager::Unload()    → libera texturas, sonidos y música
├── Init::CerrarAudio()          → cierra dispositivo de audio
└── Init::Cerrar()               → cierra ventana

Init (namespace)
├── InitVentana()                → InitWindow + SetTargetFPS
├── InitAudio()                  → InitAudioDevice
├── CerrarAudio()                → CloseAudioDevice
└── Cerrar()                     → CloseWindow

ResourceManager (clase estática)
├── texturas
│   
├── sonidos
│ 
└── música
   

Brazo
├── b2Body*                      → dinámico
├── b2RevoluteJoint*             → anclado al pivote estático, centro del brazo
├── Carga* carga                 → puntero asignado desde main
├── HandleInput(world)
│   ├── KEY_UP / KEY_DOWN        → AjustarCable en carga
│   └── KEY_Q                    → Soltar bola
└── Draw()                      

Carga
├── b2Body*                      → dinámico, circular ( un cociente relaciona radius y density)
├── b2DistanceJoint*             → anclado al extremo del brazo, largo variable
├── bool suelta                  → true una vez destruido el joint
├── Soltar                → destruye joint, aplica impulso extra
├── AjustarCable          
└── Draw(brazoBody)
    

Contraperson
├── b2Body*                      → dinámico, circular ( hay una relación entre radio y densidad : cociente)
├── b2DistanceJoint*             → anclado al extremo opuesto del brazo
├── float fuerzaActual           → se acumula mientras SPACE presionado
├── Color color                  → sigue a la acumulación de impulso
├── HandleInput()
│   ├── KEY_A / KEY_D            → ApplyForce lateral
│   └── KEY_SPACE hold/release   → acumula fuerza + cambia color / suelta impulso
└── Draw(brazoBody)              → cable + DrawTexturePro("diamante") con tint color

Torre
├── vector<Bloque>               → 6 bloques (segmentos del tótem)
│   └── Bloque { body, halfW, halfH, fila }
├── bool golpe                   → flag del ContactListener
├── SetContactListener(world, cargaBody) → registra listener en el world
├── TorreContactListener (clase anidada)
│   ├── Torre* torre             → puntero a la torre 
│   └── BeginContact(contact)    → chequea los bodies. flaguea → golpe = true
└── Draw()
    └── DrawTexturePro("torre")  → png vertical que se recorta

Ground
└── b2Body*                      → estático, piso. Hay un texto acá que podría ir en HUD pero es un detalle

LoopDeJuego
├── LoopDeJuego()               
├── ~LoopDeJuego()              
├── Run()                        → loop principal, devuelve bool
│   ├── world.Step()             
│   ├── UpdateMusicStream()      
│   ├── HandleInput()
│   ├── Draw()
│   ├── if torre.golpe           
│   └── KEY_R                    →  reiniciar (con flag)
├── HandleInput()
│   ├── brazo.HandleInput()
│   └── contraperson.HandleInput()
└── Draw()
    ├── fondo                    → DrawTexture("fondo")
    ├── ground.Draw()
    ├── torre.Draw()
    ├── brazo.Draw()
    ├── carga.Draw()
    ├── contraperson.Draw()
    └── HUD                      



## Problemas que surgieron
- No se bien como usar  los ContactListeners. Al menos no en profundidad. No entiendo como funcionan los filtros, con lo cual lo hice lo mas simple para poder darle un sonido al impacto con el tótem
- Otra cosa que se desprende de esto es que al iniciar se escucha el sonido porque los segmentos de la torre (tótem) chocan entre si o contra el piso. Para solucionar esto ( atarlo con alambre) anidé un chequeo de bola suelta.


##Notas


A mi me gusta dibujar con las primitivas de RayLib, pero el TP requería usar sprites. Tanto los pngs como la música y los sonidos  los fabriqué.






