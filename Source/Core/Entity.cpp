#include "Entity.h"

#include <cassert>
#include <algorithm>

#include "Core.h"
#include "Component.h"
#include "Transform.h"

Entity::~Entity ()
{
	for (Component* component : mComponents)
	{
		assert(component);
		unloadComponent(component, false);
		delete component;
	}
}

void Entity::update ()
{
	for (Component* component : mUpdatingComponents)
	{
		component->update();
	}
}

void Entity::startUpdating ()
{
	mUpdating = true;
}

void Entity::stopUpdating ()
{
	mUpdating = false;
}

void Entity::destroyComponent (Component* component)
{
	assert(component);
	assert(component->isLoaded());

	unloadComponent(component);

	delete component;
}

Core* Entity::getCore ()
{
	assert(mLoaded);
	return mCore;
}

Transform* Entity::getTransform ()
{
	assert(mLoaded);
	return mTransform;
}

bool Entity::isLoaded ()
{
	return mLoaded;
}

bool Entity::isUpdating ()
{
	return mUpdating;
}

void Entity::onLoad (Core* core)
{
	assert(!mLoaded);
	assert(core);
	
	mCore = core;
	mLoaded = true;

	createDefaultComponents();
}

void Entity::onUnload (Core* core)
{
	assert(mLoaded);
	assert(core);
	assert(mCore == core);
	
	mCore = nullptr;
	mLoaded = false;
}

void Entity::startUpdatingComponent(Component* component)
{
	assert(mLoaded);
	assert(component);

	mUpdatingComponents.push_back(component);
}

void Entity::stopUpdatingComponent(Component* component)
{
	assert(component);

	auto pos = std::find(mUpdatingComponents.begin(), mUpdatingComponents.end(), component);
	assert(pos != mUpdatingComponents.end());
	mUpdatingComponents.erase(pos);
}

void Entity::loadComponent (Component* component)
{
	assert(mLoaded);
	assert(component);
	assert(!component->isLoaded());

	mComponents.push_back(component);
	if (component->isUpdating())
		startUpdatingComponent(component);

	component->onLoad(this); // Call onLoad after actually loading
}

void Entity::unloadComponent (Component* component, bool findAndRemove /* = true */)
{
	// Entity may not be loaded at this point
	assert(component);
	assert(component->isLoaded());

	component->onUnload(this); // Call onUnload before actually unloading
	if (findAndRemove)
	{
		auto pos = std::find(mComponents.begin(), mComponents.end(), component);
		assert(pos != mComponents.end());
		mComponents.erase(pos);

		if (component->isUpdating())
			stopUpdatingComponent(component);
	}
}

void Entity::createDefaultComponents ()
{
	assert(mLoaded);
	mTransform = createComponent<Transform>();
}