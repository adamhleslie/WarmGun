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
		component->onUnload(this);
		// Don't need to actually remove from loaded/enabled lists
		delete component;
	}
}

void Entity::update ()
{
	for (Component* component : mEnabledComponents)
	{
		component->update();
	}
}

void Entity::enable ()
{
	mEnabled = true;
}

void Entity::disable ()
{
	mEnabled = false;
}

void Entity::destroyComponent (Component* component)
{
	assert(mLoaded);
	assert(component);
	assert(component->isLoaded());

	unloadComponent(component);

	delete component;
}

Core* Entity::getCore ()
{
	assert(mLoaded);
	assert(mCore);
	return mCore;
}

Transform* Entity::getTransform ()
{
	assert(mLoaded);
	assert(mTransform);
	return mTransform;
}

bool Entity::isLoaded ()
{
	return mLoaded;
}

bool Entity::isEnabled ()
{
	return mEnabled;
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
	assert(mCore == core);
	
	mCore = nullptr;
	mLoaded = false;
}

void Entity::enableComponent(Component* component)
{
	assert(mLoaded);
	assert(component);
	assert(component->isLoaded());

	mEnabledComponents.push_back(component);
}

void Entity::disableComponent(Component* component)
{
	assert(mLoaded);
	assert(component);
	assert(!component->isLoaded());

	auto pos = std::find(mEnabledComponents.begin(), mEnabledComponents.end(), component);
	assert(pos != mEnabledComponents.end());
	mEnabledComponents.erase(pos);
}

void Entity::loadComponent (Component* component)
{
	assert(mLoaded);
	assert(component);

	// Add component to loaded components
	mComponents.push_back(component);

	component->onLoad(this);

	// Add component to enabled components after loading
	if (component->isEnabled())
		enableComponent(component);
}

void Entity::unloadComponent (Component* component)
{
	assert(mLoaded);
	assert(component);

	// Remove component from enabled components before loading
	if (component->isEnabled())
		disableComponent(component);

	// Remove component from loaded components
	auto pos = std::find(mComponents.begin(), mComponents.end(), component);
	assert(pos != mComponents.end());
	mComponents.erase(pos);

	component->onUnload(this);
}

void Entity::createDefaultComponents ()
{
	mTransform = createComponent<Transform>();
	assert(mTransform);
}