#include "Module.h"

#include <cassert>

#include "Core.h"

void Module::enable ()
{
	if (!mEnabled)
	{
		mEnabled = true;
		if (mLoaded)
			mCore->enableModule(this);
	}
}

void Module::disable ()
{
	if (mEnabled)
	{
		mEnabled = false;
		if (mLoaded)
			mCore->disableModule(this);
	}
}

bool Module::isLoaded ()
{
	return mLoaded;
}

bool Module::isEnabled ()
{
	return mEnabled;
}

void Module::onLoad (Core* core)
{
	assert(!mLoaded);
	assert(core);
	
	mCore = core;
	onLoadCallback();
	mLoaded = true;
}

void Module::onUnload (Core* core)
{
	assert(mLoaded);
	assert(mCore == core);
	
	mCore = nullptr;
	mLoaded = false;
}