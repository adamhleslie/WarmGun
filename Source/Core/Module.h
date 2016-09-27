#pragma once

class Core;

/**
	To create a brand new module:
		1. Inherit from this class
		2. Implement, constructor, destructor, and setup()
			a. Call disable() within setup if you don't use update
		3. Increase Core::kNumModules (Core.h)
		4. Add your module to Core::getModules() (Core.cpp)
		5. Add functionality as needed - GameObjects and Components not yet implemented
**/

class Module
{
public:
	Module () {}
	virtual ~Module () {}

	void init(Core* core);
	virtual void update () {};

	bool isInitialized();
	bool isEnabled();

protected:
	// Called within init
	virtual void setup() = 0;

	// When enabled, update is called every tick
	void enable();
	// Modules begin enabled: disable may be called in setup
	void disable();

private:
	bool mEnabled = true;
	bool mInitialized = false;
	Core* mCore = nullptr;
};