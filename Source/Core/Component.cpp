#include "Component.h"

#include <cassert>

#include "Entity.h"

void Component::startUpdating ()
{
	if (!mUpdating)
	{
		mUpdating = true;
		if (mLoaded)
			mEntity->startUpdatingComponent(this);
	}
}

void Component::stopUpdating ()
{
	if (mUpdating)
	{
		mUpdating = false;
		if (mLoaded)
			mEntity->stopUpdatingComponent(this);
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

bool Component::isUpdating ()
{
	return mUpdating;
}

void Component::onLoad (Entity* entity)
{
	assert(!mLoaded);
	assert(entity);
	
	mEntity = entity;
	mLoaded = true;

	postLoad();
}

void Component::onUnload (Entity* entity)
{
	assert(mLoaded);
	assert(entity);
	assert(mEntity == entity);
	
	preUnload();

	mEntity = nullptr;
	mLoaded = false;
}