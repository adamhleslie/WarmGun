#include "Module.h"

#include <cassert>

#include "Core.h"

void Module::init (Core* core)
{
	assert(!mInitialized);
	assert(core);
	
	mCore = core;
	setup();
	mInitialized = true;
}

bool Module::isInitialized ()
{
	return mInitialized;
}

bool Module::isEnabled ()
{
	return mEnabled;
}

void Module::enable ()
{
	assert(mInitialized);
	if (!mEnabled)
	{
		mEnabled = true;
		mCore->enableModule(this);
	}
}

void Module::disable ()
{
	if (mEnabled)
	{
		mEnabled = false;
		if (mInitialized)
			mCore->disableModule(this);
	}
}
