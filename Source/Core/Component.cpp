#include "Component.h"

#include <cassert>

#include "Entity.h"

void Component::onLoad (Entity* entity)
{
	assert(!mLoaded);
	assert(entity);
	
	mEntity = entity;
	mLoaded = true;

	onLoadCallback();
}

void Component::onUnload (Entity* entity)
{
	assert(mLoaded);
	assert(mEntity == entity);
	
	mEntity = nullptr;
	mLoaded = false;
}

bool Component::isLoaded ()
{
	return mLoaded;
}

bool Component::isEnabled ()
{
	return mEnabled;
}

void Component::enable ()
{
	mEnabled = true;
	if (mLoaded)
		mEntity->enableComponent(this);
}

void Component::disable ()
{
	mEnabled = false;
	if (mLoaded)
		mEntity->disableComponent(this);
}
