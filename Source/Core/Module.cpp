#include "Module.h"

#include <cassert>

#include "Core.h"

void Module::startUpdating ()
{
	mUpdating = true;
	if (mLoaded)
		mCore->startUpdatingModule(this);
}

void Module::stopUpdating ()
{
	mUpdating = false;
	if (mLoaded)
		mCore->stopUpdatingModule(this);
}

Core* Module::getCore ()
{
	assert(mLoaded);
	return mCore;
}

bool Module::isLoaded ()
{
	return mLoaded;
}

bool Module::isUpdating ()
{
	return mUpdating;
}

void Module::onLoad (Core* core)
{
	assert(!mLoaded);
	assert(core);
	
	mCore = core;
	mLoaded = true;

	postLoad();
}

void Module::onUnload (Core* core)
{
	assert(mLoaded);
	assert(core);
	assert(mCore == core);
	
	preUnload();

	mCore = nullptr;
	mLoaded = false;
}