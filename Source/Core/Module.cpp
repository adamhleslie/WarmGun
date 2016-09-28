#include "Module.h"

#include <cassert>

#include "Core.h"

void Module::init (Core* core)
{
	assert(!mInitialized);
	assert(core);
	
	mCore = core;
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
	if (!mEnabled)
	{
		mEnabled = true;
		if (mInitialized)
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
