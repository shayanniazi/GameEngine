# GameEngine
ECS based game engine.
Using openGL as the rendering API and SDL for low level input and window handling

Each entity is just an ID that has information about where it's components are stored in the 'component database'. The actual 
data of the entities components are stored in contiguous blocks of memory for cache efficiency. 

See 'Game.cpp' for more information on how to create entities, components and systems, as well as to have a quick overview of
the general layout of the engine

In addition to the above, check out the following systems to understand how to create systems and components:

Systems:
1) HealthSystem.cpp
2) RenderingSystem.cpp

Components:
1) HealthComponent.h
2) TransformComponent.h
