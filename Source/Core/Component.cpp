#include "Component.h"

#include <cassert>

#include "Entity.h"

void Component::enable ()
{
	if (!mEnabled)
	{
		mEnabled = true;
		if (mLoaded)
			mEntity->enableComponent(this);
	}
}

void Component::disable ()
{
	if (mEnabled)
	{
		mEnabled = false;
		if (mLoaded)
			mEntity->disableComponent(this);
	}
}

Entity* Component::getEntity ()
{
	assert(mLoaded);
	return mEntity;
}

bool Component::isLoaded ()
{
	return mLoaded;
}

bool Component::isEnabled ()
{
	return mEnabled;
}

void Component::onLoad (Entity* entity)
{
	assert(!mLoaded);
	assert(entity);
	
	mEntity = entity;
	onLoadCallback();
	mLoaded = true;
}

void Component::onUnload (Entity* entity)
{
	assert(mLoaded);
	assert(mEntity == entity);
	
	mEntity = nullptr;
	mLoaded = false;
}