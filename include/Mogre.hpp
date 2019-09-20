#pragma once
// External interface

namespace Mogre
{
struct ThreadData;
// Prepare Ogre
ThreadData* Initialize();

// This is called every update on the logic thread
typedef void (*UpdateFunc)(float frameTime);
void SetUpdateCallback(UpdateFunc);

// Start Ogre
void Run(ThreadData* threadData);

// Runtime functions for creating and moving entities
class GameEntity;

GameEntity* CreateGameEntity(const char* meshName, float* vPos, float* qRot);
void MoveGameEntity(GameEntity* entity, float* vPos, float* qRot);
}  // namespace Mogre
