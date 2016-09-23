#include <cassert>

#include "Core.h"
#include "Module.h"
#include "Renderer.h"
#include "Scene1.h"

Core::Core ()
{
	mModules.fill(nullptr);
}

Core::~Core ()
{
	for (auto module = mModules.begin(); module != mModules.end(); module++)
	{
		if (*module)
			delete *module;
	}
}

// Initialize Modules before run()
void Core::init ()
{
	// Initialize the Renderer before anything else
	mRenderer = new Renderer();
	mRenderer->init();

	mModules[0] = mRenderer;
	mModules[1] = new Scene1(mRenderer, Ogre::ST_GENERIC);

	// init modules, skipping renderer
	for (int i = 1; i < kNumModules; i++)
	{
		mModules[i]->init();
	}

	mInitialized = true;
}

// The Game Loop
void Core::run ()
{
	assert(mInitialized);
	Ogre::Timer timer = Ogre::Timer();

	constexpr unsigned long kTimeStep = 4;

	unsigned long accumulator = 0.0;
	unsigned long time = timer.getMilliseconds();
	
	while (mRenderer->mRunning)
	{
		unsigned long newTime = timer.getMilliseconds();
		accumulator += newTime - time;
		time = newTime;

		while (accumulator >= kTimeStep)
		{
			for (auto module = mModules.begin(); module != mModules.end(); module++)
			{
				(*module)->update();
			}

			accumulator -= kTimeStep;
		}

		Ogre::WindowEventUtilities::messagePump();
		mRenderer->mRoot->renderOneFrame();
	}
}