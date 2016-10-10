#include "Core.h"

#include <cassert>
#include <algorithm>

#include "Entity.h"
#include "Module.h"
#include "Renderer.h"

/// Add Modules below ///
#include "SceneController.h"
#include "Audio.h"
#include "GUI.h"
#include "InputManager.h"

void Core::createModules ()
{
	mRenderer = new Renderer(Ogre::ST_GENERIC);
	loadModule(mRenderer);
	
	//loadModule(new Audio());
	loadModule(new GUI(mRenderer->getRenderWindow()));

	//Setup

	// OIS::KeyListener* keyTest = dynamic_cast<OIS::KeyListener*>(mInputMgr);
 //    OIS::MouseListener* mouseTest = dynamic_cast<OIS::MouseListener*>(mInputMgr);
	//mInputMgr = InputManager::getSingletonPtr();
    //mInputMgr->initialise( mRenderer->getRenderWindow() );


    //assert(keyTest!=0 && mouseTest!=0);
    //mInputMgr->addKeyListener( (OIS::KeyListener*)mInputMgr, "keyListener" );
    //mInputMgr->addMouseListener( (OIS::MouseListener*)mInputMgr, "mouseListener" );

	mInputMgr = new InputManager(mRenderer->getRenderWindow());
	// mInputMgr->addKeyListener( mInputMgr, "KeyListener" );
 //    mInputMgr->addMouseListener( mInputMgr, "MouseListener" );
	loadModule(mInputMgr);

	// Create SceneController last, since it sets up the initial scene
	loadModule(new SceneController(mRenderer));
}
/// Add Modules above ///

Core::Core ()
{
	constexpr size_t kNumModules = 5;
	static_assert(kNumModules >= 1, "Make room for the Renderer module!");
	mModules.reserve(kNumModules);
	
	createModules();
	assert(mRenderer);
}

Core::~Core ()
{
	destroyAllEntities();
	for (Module* module : mModules)
	{
		assert(module);
		unloadModule(module, false);
		delete module;
	}
}

// The Game Loop
void Core::run ()
{
	Ogre::Timer timer = Ogre::Timer();

	unsigned long accumulator = 0.0;
	unsigned long time = timer.getMilliseconds();
	
	while (mRenderer->mRunning)
	{
		// OIS::KeyCode lastKey = InputManager->lastKeyPressed();


		// if(lastKey == OIS::KC_ESCAPE) {
		// 	// close window when ESC is pressed
		// 	mRunning = false;
		// }



		unsigned long newTime = timer.getMilliseconds();
		accumulator += newTime - time;
		time = newTime;

		while (accumulator >= kTimeStep)
		{
			for (Entity* entity : mEntities)
			{
				if (entity->isUpdating())
					entity->update();
			}

			for (Module* module : mUpdatingModules)
			{
				module->update();
			}

			accumulator -= kTimeStep;
		}

		mRenderer->renderOneFrame();
	}
}

Entity* Core::createEntity ()
{
	Entity* entity = new Entity();
	mEntities.push_back(entity);
	entity->onLoad(this); // Call onLoad after actually loading

	return entity;
}

void Core::destroyEntity (Entity* entity, bool findAndRemove /* = true */)
{
	assert(entity);
	assert(entity->isLoaded());

	entity->onUnload(this); // Call onUnload before actually unloading
	if (findAndRemove)
	{
		auto pos = std::find(mEntities.begin(), mEntities.end(), entity);
		assert(pos != mEntities.end());
		mEntities.erase(pos);
	}

	delete entity;
}

void Core::destroyAllEntities ()
{
	for (Entity* entity : mEntities)
	{
		destroyEntity(entity, false);
	}
	mEntities.clear();
}

Renderer* Core::getRenderer ()
{
	return mRenderer;
}

// module should not be in mUpdatingModules
void Core::startUpdatingModule (Module* module)
{
	assert(module);

	mUpdatingModules.push_back(module);
}

// module should be in mUpdatingModules
void Core::stopUpdatingModule (Module* module)
{
	assert(module);

	auto pos = std::find(mUpdatingModules.begin(), mUpdatingModules.end(), module);
	assert(pos != mUpdatingModules.end());
	mUpdatingModules.erase(pos);
}

void Core::loadModule (Module* module)
{
	assert(module);
	assert(!module->isLoaded());

	mModules.push_back(module);
	if (module->isUpdating())
		startUpdatingModule(module);

	module->onLoad(this); // Call onLoad after actually loading
}

void Core::unloadModule (Module* module, bool findAndRemove /* = true */)
{
	assert(module);
	assert(module->isLoaded());

	module->onUnload(this); // Call onUnload before actually unloading
	if (findAndRemove)
	{
		auto pos = std::find(mModules.begin(), mModules.end(), module);
		assert(pos != mModules.end());
		mModules.erase(pos);

		if (module->isUpdating())
			stopUpdatingModule(module);
	}
}


// bool Core::Quit(const CEGUI::EventArgs& e) {

// 	mRenderer->mRunning = false;
//     return true;
// }

// bool Core::Replay(const CEGUI::EventArgs &e) {

// 	//TODO: reset values, start again
// 	return true;
// }
