#include "Core.h"

#include <cassert>
#include <algorithm>

#include "Entity.h"
#include "Module.h"
#include "Renderer.h"
#include "Audio.h"

/// Add Modules below ///
#include "SceneController.h"

void Core::loadModules ()
{
	mRenderer = new Renderer();

	mModules[0] = mRenderer;
	mModules[1] = new SceneController(mRenderer, Ogre::ST_GENERIC);
	mModules[2] = new Audio();
	// make sure mModules[max], max == kNumModules - 1
}
/// Add Modules above ///

Core::Core ()
{
	mModules.fill(nullptr);
	
	loadModules();

	// let modules know they are loaded
	for (Module* module : mModules)
	{
		module->onLoad(this);
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
		assert(module);
		module->onUnload(this);
		delete module;
	}
	for (Entity* entity : mEntities)
	{
		assert(entity);
		entity->onUnload(this);
		delete entity;
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
			for (Entity* entity : mEntities)
			{
				if (entity->isEnabled())
					entity->update();
			}

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

Entity* Core::createEntity ()
{
	Entity* entity = new Entity();
	mEntities.push_back(entity);
	entity->onLoad(this);

	return entity;
}

void Core::destroyEntity (Entity* entity)
{
	auto pos = std::find(mEntities.begin(), mEntities.end(), entity);
	assert(pos != mEntities.end());
	mEntities.erase(pos);

	entity->onUnload(this);

	delete entity;
}

// template <class M>
// M* Core::getModule()
// {
// 	static_assert(std::is_base_of<Module, M>::value, 
// 			      "getModule: templated type must be derived from Module");

// 	for (Module* module : mModules)
// 	{
// 		if (dynamic_cast<M*>(module))
// 			return module;
// 	}
// }

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