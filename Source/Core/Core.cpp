#include "Core.h"

#include <cassert>
#include <algorithm>

#include "Module.h"
#include "Renderer.h"


/// Add Modules below ///
#include "SceneController.h"

void Core::getModules ()
{
	mRenderer = new Renderer();

	mModules[0] = mRenderer;
	mModules[1] = new SceneController(mRenderer, Ogre::ST_GENERIC);
	// make sure mModules[max], max == kNumModules - 1
}
/// Add Modules above ///


Core::Core ()
{
	mModules.fill(nullptr);
	
	getModules();

	// init modules
	for (Module* module : mModules)
	{
		module->init(this);
	}

	// place enabled (updating) modules into their container
	for (Module* module : mModules)
	{
		if (module->isEnabled())
			mEnabledModules.push_back(module);
	}
}

Core::~Core ()
{
	for (Module* module : mModules)
	{
		if (module)
			delete module;
	}
}

// The Game Loop
void Core::run ()
{
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
			for (Module* module : mEnabledModules)
			{
				module->update();
			}

			accumulator -= kTimeStep;
		}

		Ogre::WindowEventUtilities::messagePump();
		mRenderer->mRoot->renderOneFrame();
	}
}

// module should not be in mEnabledModules
void Core::enableModule (Module* module)
{
	mEnabledModules.push_back(module);
}

// module should be in mEnabledModules
void Core::disableModule (Module* module)
{
	auto pos = std::find(mEnabledModules.begin(), mEnabledModules.end(), module);
	assert(pos != mEnabledModules.end());

    mEnabledModules.erase(pos);
}