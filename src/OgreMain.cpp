
#include "GameEntityManager.h"
#include "GraphicsGameState.h"
#include "GraphicsSystem.h"
#include "LogicGameState.h"
#include "LogicSystem.h"

#include "Threading/YieldTimer.h"

#include "OgreRenderWindow.h"
#include "OgreTimer.h"

#include "Threading/OgreBarrier.h"
#include "Threading/OgreThreads.h"

#include <iostream>

extern const double cFrametime;
const double cFrametime = 1.0 / 25.0;

extern bool gFakeFrameskip;
bool gFakeFrameskip = false;

extern bool gFakeSlowmo;
bool gFakeSlowmo = false;

unsigned long renderThread(Ogre::ThreadHandle* threadHandle);
unsigned long logicThread(Ogre::ThreadHandle* threadHandle);
THREAD_DECLARE(renderThread);
THREAD_DECLARE(logicThread);

struct ThreadData
{
	Demo::GraphicsSystem* graphicsSystem;
	Demo::LogicSystem* logicSystem;
	Ogre::Barrier* barrier;
};

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main()
#endif
{
	Mogre::GraphicsGameState graphicsGameState;
	Demo::GraphicsSystem graphicsSystem(&graphicsGameState);
	Mogre::LogicGameState logicGameState;
	Demo::LogicSystem logicSystem(&logicGameState);
	Ogre::Barrier barrier(2);

	graphicsGameState._notifyGraphicsSystem(&graphicsSystem);
	logicGameState._notifyLogicSystem(&logicSystem);

	graphicsSystem._notifyLogicSystem(&logicSystem);
	logicSystem._notifyGraphicsSystem(&graphicsSystem);

	Demo::GameEntityManager gameEntityManager(&graphicsSystem, &logicSystem);

	ThreadData threadData;
	threadData.graphicsSystem = &graphicsSystem;
	threadData.logicSystem = &logicSystem;
	threadData.barrier = &barrier;

	Ogre::ThreadHandlePtr threadHandles[2];
	threadHandles[0] = Ogre::Threads::CreateThread(THREAD_GET(renderThread), 0, &threadData);
	threadHandles[1] = Ogre::Threads::CreateThread(THREAD_GET(logicThread), 1, &threadData);

	Ogre::Threads::WaitForThreads(2, threadHandles);

	return 0;
}

//---------------------------------------------------------------------
unsigned long renderThreadApp(Ogre::ThreadHandle* threadHandle)
{
	ThreadData* threadData = reinterpret_cast<ThreadData*>(threadHandle->getUserParam());
	Demo::GraphicsSystem* graphicsSystem = threadData->graphicsSystem;
	Ogre::Barrier* barrier = threadData->barrier;

	graphicsSystem->initialize("Tutorial 06: Multithreading");
	barrier->sync();

	if (graphicsSystem->getQuit())
	{
		graphicsSystem->deinitialize();
		return 0;  // User cancelled config
	}

	graphicsSystem->createScene01();
	barrier->sync();

	graphicsSystem->createScene02();
	barrier->sync();

	Ogre::RenderWindow* renderWindow = graphicsSystem->getRenderWindow();

	Ogre::Timer timer;

	Ogre::uint64 startTime = timer.getMicroseconds();

	double timeSinceLast = 1.0 / 60.0;

	while (!graphicsSystem->getQuit())
	{
		graphicsSystem->beginFrameParallel();
		graphicsSystem->update(timeSinceLast);
		graphicsSystem->finishFrameParallel();

		if (!renderWindow->isVisible())
		{
			// Don't burn CPU cycles unnecessary when we're minimized.
			Ogre::Threads::Sleep(500);
		}

		if (gFakeFrameskip)
			Ogre::Threads::Sleep(120);

		Ogre::uint64 endTime = timer.getMicroseconds();
		timeSinceLast = (endTime - startTime) / 1000000.0;
		timeSinceLast = std::min(1.0, timeSinceLast);  // Prevent from going haywire.
		startTime = endTime;
	}

	barrier->sync();

	graphicsSystem->destroyScene();
	barrier->sync();

	graphicsSystem->deinitialize();
	barrier->sync();

	return 0;
}
unsigned long renderThread(Ogre::ThreadHandle* threadHandle)
{
	unsigned long retVal = -1;

	try
	{
		retVal = renderThreadApp(threadHandle);
	}
	catch (Ogre::Exception& e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occured!",
		            MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
#endif

		abort();
	}

	return retVal;
}
//---------------------------------------------------------------------
unsigned long logicThread(Ogre::ThreadHandle* threadHandle)
{
	ThreadData* threadData = reinterpret_cast<ThreadData*>(threadHandle->getUserParam());
	Demo::GraphicsSystem* graphicsSystem = threadData->graphicsSystem;
	Demo::LogicSystem* logicSystem = threadData->logicSystem;
	Ogre::Barrier* barrier = threadData->barrier;

	logicSystem->initialize();
	barrier->sync();

	if (graphicsSystem->getQuit())
	{
		logicSystem->deinitialize();
		return 0;  // Render thread cancelled early
	}

	logicSystem->createScene01();
	barrier->sync();

	logicSystem->createScene02();
	barrier->sync();

	Ogre::RenderWindow* renderWindow = graphicsSystem->getRenderWindow();

	Ogre::Timer timer;
	Demo::YieldTimer yieldTimer(&timer);

	Ogre::uint64 startTime = timer.getMicroseconds();

	while (!graphicsSystem->getQuit())
	{
		logicSystem->beginFrameParallel();
		logicSystem->update(static_cast<float>(cFrametime));
		logicSystem->finishFrameParallel();

		logicSystem->finishFrame();

		if (gFakeSlowmo)
			Ogre::Threads::Sleep(120);

		if (!renderWindow->isVisible())
		{
			// Don't burn CPU cycles unnecessary when we're minimized.
			Ogre::Threads::Sleep(500);
		}

		// YieldTimer will wait until the current time is greater than startTime +
		// cFrametime
		startTime = yieldTimer.yield(cFrametime, startTime);
	}

	barrier->sync();

	logicSystem->destroyScene();
	barrier->sync();

	logicSystem->deinitialize();
	barrier->sync();

	return 0;
}
