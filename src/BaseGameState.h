#pragma once

#include "OgrePrerequisites.h"

#include "GameState.h"

namespace Ogre
{
namespace v1
{
class TextAreaOverlayElement;
}
}  // namespace Ogre

namespace Demo
{
class GraphicsSystem;
class CameraController;
}  // namespace Demo

namespace Mogre
{

class BaseGameState : public Demo::GameState
{
protected:
	Demo::GraphicsSystem* mGraphicsSystem;

	/// Optional, for controlling the camera with WASD and the mouse
	Demo::CameraController* mCameraController;

	Ogre::uint16 mDisplayHelpMode;
	Ogre::uint16 mNumDisplayHelpModes;

	Ogre::v1::TextAreaOverlayElement* mDebugText;
	Ogre::v1::TextAreaOverlayElement* mDebugTextShadow;

	virtual void createDebugTextOverlay(void);
	virtual void generateDebugText(float timeSinceLast, Ogre::String& outText);

public:
	BaseGameState();
	virtual ~BaseGameState();

	void _notifyGraphicsSystem(Demo::GraphicsSystem* graphicsSystem);

	virtual void createScene01(void);

	virtual void update(float timeSinceLast);

	virtual void keyPressed(const SDL_KeyboardEvent& arg);
	virtual void keyReleased(const SDL_KeyboardEvent& arg);

	virtual void mouseMoved(const SDL_Event& arg);
};
}  // namespace Mogre
