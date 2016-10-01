#include "Entity.h"

#include <cassert>
#include <algorithm>
#include <type_traits>

#include "Core.h"
#include "Component.h"

Entity::~Entity ()
{
	for (Component* component : mComponents)
	{
		assert(component);
		component->onUnload(this);
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

template <class C> 
C* Entity::createComponent ()
{
	static_assert(std::is_base_of<Component, C>::value, 
				  "createComponent: templated type must be derived from Component");
	Component* component = static_cast<Component*>(new C());

	loadComponent(component);

	return component;
}

void Entity::destroyComponent (Component* component)
{
	assert(component->isLoaded());

	unloadComponent(component);

	delete component;
}

template <class C> 
C* Entity::getComponent ()
{
	static_assert(std::is_base_of<Component, C>::value, 
				  "getComponent: templated type must be derived from Component");
	
	for (Component* component : mComponents)
	{
		if (dynamic_cast<C*>(component))
			return component;
	}

	return nullptr;
}

Core* Entity::getCore ()
{
	assert(mLoaded);
	return mCore;
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
}

void Entity::onUnload (Core* core)
{
	assert(mLoaded);
	assert(mCore == core);
	
	mCore = nullptr;
	mLoaded = false;
}

// Component should be loaded already, and not enabled
void Entity::enableComponent(Component* component)
{
	mEnabledComponents.push_back(component);
}

// Component should be loaded and enabled already
void Entity::disableComponent(Component* component)
{
	auto pos = std::find(mEnabledComponents.begin(), mEnabledComponents.end(), component);
	assert(pos != mEnabledComponents.end());
	mEnabledComponents.erase(pos);
}

void Entity::loadComponent (Component* component)
{
	// Add component to loaded components
	mComponents.push_back(component);

	component->onLoad(this);

	// Add component to enabled components
	if (component->isEnabled())
		enableComponent(component);
}

void Entity::unloadComponent (Component* component)
{
	// Remove component from loaded components
	auto pos = std::find(mComponents.begin(), mComponents.end(), component);
	assert(pos != mComponents.end());
	mComponents.erase(pos);

	component->onUnload(this);

	// Remove component from enabled components
	if (component->isEnabled())
		disableComponent(component);
}