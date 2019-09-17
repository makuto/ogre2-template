
#include "GraphicsGameState.h"
#include "GraphicsSystem.h"

#include "OgreItem.h"
#include "OgreSceneManager.h"

extern const double cFrametime;
extern bool gFakeSlowmo;
extern bool gFakeFrameskip;

namespace Mogre
{
GraphicsGameState::GraphicsGameState() : mEnableInterpolation(true)
{
}
//-----------------------------------------------------------------------------------
void GraphicsGameState::generateDebugText(float timeSinceLast, Ogre::String& outText)
{
}
//-----------------------------------------------------------------------------------
void GraphicsGameState::update(float timeSinceLast)
{
	float weight = mGraphicsSystem->getAccumTimeSinceLastLogicFrame() / cFrametime;
	weight = std::min(1.0f, weight);

	if (!mEnableInterpolation)
		weight = 0;

	mGraphicsSystem->updateGameEntities(mGraphicsSystem->getGameEntities(Ogre::SCENE_DYNAMIC),
	                                    weight);

	BaseGameState::update(timeSinceLast);
}
//-----------------------------------------------------------------------------------
void GraphicsGameState::keyReleased(const SDL_KeyboardEvent& arg)
{
	if ((arg.keysym.mod & ~(KMOD_NUM | KMOD_CAPS)) != 0)
	{
		BaseGameState::keyReleased(arg);
		return;
	}

	if (arg.keysym.sym == SDLK_F4)
	{
		// mEnableInterpolation = !mEnableInterpolation;
	}
	else
	{
		BaseGameState::keyReleased(arg);
	}
}
}  // namespace Mogre
