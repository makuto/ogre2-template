#pragma once

#include "OgrePrerequisites.h"
#include "GameState.h"

namespace Demo
{
class LogicSystem;
struct GameEntity;
struct MovableObjectDefinition;
}  // namespace Demo

namespace Mogre
{

class LogicGameState : public Demo::GameState
{
	float mDisplacement;
	Demo::GameEntity* mCubeEntity;
	Demo::MovableObjectDefinition* mCubeMoDef;

	Demo::LogicSystem* mLogicSystem;

public:
	LogicGameState();
	~LogicGameState();

	void _notifyLogicSystem(Demo::LogicSystem* logicSystem)
	{
		mLogicSystem = logicSystem;
	}

	virtual void createScene01(void);
	virtual void update(float timeSinceLast);
};
}  // namespace Mogre
