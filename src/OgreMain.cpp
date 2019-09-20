#include "Mogre.hpp"

#include "OgreRenderWindow.h"
#include "OgreTimer.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main()
#endif
{
	Mogre::ThreadData* threadData = Mogre::Initialize();
	Mogre::Run(threadData);

	return 0;
}
