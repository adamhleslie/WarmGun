#pragma once

class Core;

/**
	To create a brand new module:
		0. Create a new folder for it, and add it to CMakeLists.txt with add_project_module
		1. Inherit from this class
		2. Implement constructor and destructor
			a. Call disable() within your constructor if you don't want your module to start updating
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
	// When enabled, update is called every tick - Modules begin enabled
	void enable();
	void disable();

private:
	bool mEnabled = true;
	bool mInitialized = false;
	Core* mCore = nullptr;
};