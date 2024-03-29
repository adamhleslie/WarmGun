#include "Core.h"

#include <cassert>
#include <algorithm>
#include <btBulletDynamicsCommon.h>
#include <OgreSceneNode.h>

#include "Entity.h"
#include "Module.h"
#include "Renderer.h"
#include "Physics.h"
#include "Transform.h"

/// Add Modules below ///
#include "SceneController.h"

using Ogre::Vector3;

void Core::createModules ()
{
	mRenderer = new Renderer(Ogre::ST_GENERIC);
	loadModule(mRenderer);

	mPhysics = new Physics();
	loadModule(mPhysics);

	// Create SceneController last, since it sets up the initial scene
	loadModule(new SceneController(mRenderer));
}
/// Add Modules above ///

Core::Core ()
{
	constexpr size_t kNumModules = 6;
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
		unsigned long newTime = timer.getMilliseconds();
		accumulator += newTime - time;
		time = newTime;

		while (accumulator >= kTimeStepMs)
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

			// Update physics
			mPhysics->getWorld()->stepSimulation(kTimeStepS, 0);

			accumulator -= kTimeStepMs;
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

Entity* Core::createEntity (Shape shape, 
							const string& material, 
							bool castShadows, 
							const Vector3& size /* Vector3::UNIT_SCALE */, 
							const Vector3& position /* = Vector3::ZERO */, 
							const Quaternion& rotation /* = Quaternion::IDENTITY */)
{
	Entity* entity = createEntity();
	Transform* transf = entity->getTransform();
	Ogre::SceneNode* node = transf->getSceneNode();

	// Add mesh
	Ogre::Entity* mesh = nullptr;
	Ogre::SceneManager::PrefabType meshType;
	switch (shape)
	{
		case kCube:
			meshType = Ogre::SceneManager::PT_CUBE;
			break;

		case kSphere:
			meshType = Ogre::SceneManager::PT_SPHERE;
			break;

		default:
			meshType = Ogre::SceneManager::PT_CUBE;
			break;
	}
	mesh = mRenderer->getSceneManager()->createEntity(meshType);

	assert(mesh);
	mesh->setCastShadows(castShadows);
	mesh->setMaterialName(material);
	node->attachObject(mesh);

	node->setScale(size);
	node->setPosition(position);
	node->setOrientation(rotation);

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

Physics* Core::getPhysics ()
{
	return mPhysics;
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
