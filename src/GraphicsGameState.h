#pragma once

#include "OgrePrerequisites.h"
#include "BaseGameState.h"

#include "OgreVector3.h"

namespace Mogre
{
class GraphicsSystem;

class GraphicsGameState : public BaseGameState
{
	bool mEnableInterpolation;

	virtual void generateDebugText(float timeSinceLast, Ogre::String& outText);

public:
	GraphicsGameState();

	virtual void update(float timeSinceLast);

	virtual void keyReleased(const SDL_KeyboardEvent& arg);
};
}  // namespace Mogre
